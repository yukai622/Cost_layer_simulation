#include "stdio.h"
#include "stdlib.h"
#include "p_battery.h"
#include "c_battery.h"
#include "p_bus.h"
#include "c_bus.h"
#include "p_pv.h"
#include "c_pv.h"
#include "p_wt.h"
#include "c_wt.h"
#include "battery_converter.h"
#include "pv_converter.h"
#include "wind_inverter.h"
#include "p_house1.h"
#include "c_house1.h"
#include "p_house2.h"
#include "c_house2.h"
#include "p_house5.h"
#include "c_house5.h"
#include "c_grid.h"
#include "tstep.h"




int sc_main(int argc, char* argv[]){

	sc_core::sc_set_time_resolution(1.0,sc_core::SC_SEC);	

	// Get PV array and battery bank configurations
	int batt_s = atoi(argv[1]);
	int batt_p = atoi(argv[2]);
	int pv_num = atoi(argv[3]);


	//Signals for battery module in power layer
	sca_tdf::sca_signal<double> Ibatt, Vbatt, SOC, Ibatt_cnv;

	//Signals for PV module in power layer
	sca_tdf::sca_signal<double> Power_pv, Ipv_cnv, sun_irradiance;  

	//Signals for wind turbine in power layer
	sca_tdf::sca_signal<double> Power_wind, Iwind_inv, wind_speed;

	sca_tdf::sca_signal<double> Phouse1, Phouse2, Phouse5;	

	sca_tdf::sca_signal<double> buy, sell;	


	// Signals for electricity from grid
	sca_tdf::sca_signal<double> c_price, depr_battery, mo_battery, depr_pv, mo_pv, depr_wt, mo_wt;
	sca_tdf::sca_signal<double> total_profit;
	sca_tdf::sca_signal<double> SOH,replace_battery;
	sca_tdf::sca_signal<double> c_h1, c_h2, c_h5;
	sca_tdf::sca_signal<double> ownuse_cost,buy_cost,sell_cost;

	// Inst in power layer
	p_battery p_batt("p_batt");
	p_pv p_pv("p_pv");
	p_wt p_wt("p_wt");

	converter_b batt_con("batt_con");
	converter_pv pv_con("pv_con");
	inverter_wt wt_inv("wt_inv");

	p_house1 p_house1("p_house1");	
	p_house2 p_house2("p_house2");	
	p_house5 p_house5("p_house5");	

	p_bus p_bus("p_bus");

	// Inst in cost layer
	c_grid c_grid("c_grid");

	c_battery c_battery("c_battery");
	c_pv c_pv("c_pv");
	c_wt c_wt("c_wt");

	c_bus c_bus("c_bus");

	c_house1 c_house1("c_house1");
	c_house2 c_house2("c_house2");
	c_house5 c_house5("c_house5");


	// Pass the data from command line
	p_batt.voc->set_data(batt_s,batt_p);
	p_pv.set_data(pv_num);
	c_battery.set_data(batt_s,batt_p);
	c_pv.set_data(pv_num);


	//----------------------Binding in powerlayer-----------------------

	//Battery
	p_batt.I(Ibatt);
	p_batt.V(Vbatt);
	p_batt.replace(replace_battery);
	p_batt.SOC(SOC);
	p_batt.SOH(SOH);

	//Battery converter
	batt_con.in(Vbatt);
	batt_con.in2(Ibatt_cnv);
	batt_con.out(Ibatt);	

	//PV panel
	p_pv.P(Power_pv);
	p_pv.sun_irradiance(sun_irradiance);

	//PV converter
	pv_con.in(Power_pv);
	pv_con.out(Ipv_cnv);

	//Wind turbine
	p_wt.power(Power_wind);
	p_wt.windspeed(wind_speed);

	//Wind inverter
	wt_inv.Pwind(Power_wind);
	wt_inv.I(Iwind_inv);

	//Load side -> A village is filled with 1 2 5 houses' combination.
	p_house1.out(Phouse1);
	p_house2.out(Phouse2);
	p_house5.out(Phouse5);

	//BUS in the power layer
	p_bus.SOC(SOC);
	p_bus.Ibatt_cnv(Ibatt_cnv);
	p_bus.Ipv_cnv(Ipv_cnv);
	p_bus.Iwind_inv(Iwind_inv);

	p_bus.Phouse1(Phouse1);		
	p_bus.Phouse2(Phouse2);		
	p_bus.Phouse5(Phouse5);		

	p_bus.Buy_from_grid(buy);		
	p_bus.Sell_to_grid(sell);	
	p_bus.total_sell_cost(buy_cost);
	p_bus.total_buy_cost(sell_cost);
	p_bus.own_use_cost(ownuse_cost);

	// Gird in the cost layer
	c_grid.out(c_price);	

	c_battery.in1(Ibatt);
	c_battery.in2(Vbatt);
	c_battery.in3(SOH);
	c_battery.out1(depr_battery);
	c_battery.out2(mo_battery);
	c_battery.out3(replace_battery);


	//PV in the cost layer
	c_pv.in(Power_pv);
	c_pv.out1(depr_pv);
	c_pv.out2(mo_pv);


	c_wt.in(Power_wind);
	c_wt.out2(mo_wt);
	c_wt.out1(depr_wt);

	c_house1.power(Phouse1);
	c_house1.price(c_price);
	c_house1.buy(buy);
	c_house1.out(c_h1);


	c_house2.power(Phouse2);
	c_house2.price(c_price);
	c_house2.buy(buy);
	c_house2.out(c_h2);


	c_house5.power(Phouse5);
	c_house5.price(c_price);
	c_house5.buy(buy);
	c_house5.out(c_h5);

	c_bus.c_h1(c_h1);
	c_bus.c_h2(c_h2);
	c_bus.c_h5(c_h5);
	c_bus.sell(sell);
	c_bus.out(total_profit);



	//sca_util::sca_decimation(1000);
	//To store the values during simualtion
	sca_util::sca_trace_file* atf = sca_util::sca_create_tabular_trace_file( "test.txt" );

//	atf->set_mode(sca_decimation(60));

	//Selecting signals to track

	//	sca_util::sca_trace(atf,total_profit,"Total");
	//	sca_util::sca_trace(atf,c_price,"Price");
	//	sca_util::sca_trace(atf,c_h1,"Cost");
	//	sca_util::sca_trace(atf,c_h2,"Cost");
	//	sca_util::sca_trace(atf,c_h5,"Cost");
	//	sca_util::sca_trace(atf,cost_pv,"PV_DEPR");
		
	//	sca_util::sca_trace(atf,buy,"BUY");
	//	sca_util::sca_trace(atf,sell,"SELL");
	//	sca_util::sca_trace(atf,buy_cost,"BUYCOST");
	//	sca_util::sca_trace(atf,sell_cost,"SELLCOST");
	//	sca_util::sca_trace(atf,ownuse_cost,"OWNUSECOST");

//		sca_util::sca_trace(atf,Ibatt,"Ibatt");
//		sca_util::sca_trace(atf,depr_battery,"depr_battery");
//		sca_util::sca_trace(atf,mo_battery,"mo_battery");
	//	sca_util::sca_trace(atf,SOC,"SOC");
//		sca_util::sca_trace(atf,Vbatt,"Vbatt");
	//	sca_util::sca_trace(atf,Phouse1,"Phouse1");
	//	sca_util::sca_trace(atf,Phouse2,"Phouse2");
	//	sca_util::sca_trace(atf,Phouse5,"Phouse5");

	//	sca_util::sca_trace(atf,wind_speed,"Wind");
	//	sca_util::sca_trace(atf,depr_pv,"depr_pv");
	//	sca_util::sca_trace(atf,mo_pv,"mo_pv");
	//	sca_util::sca_trace(atf,Iwind_inv,"Wind_current");
	//	sca_util::sca_trace(atf,depr_wt,"depr_wt");
	//	sca_util::sca_trace(atf,mo_wt,"mo_wt");
	//	sca_util::sca_trace(atf,Ipv_cnv,"Pv_current");
	//	sca_util::sca_trace(atf,Power_wind,"Power_wind");

	//	sca_util::sca_trace(atf,sun_irradiance,"Sun_profile");
	//	sca_util::sca_trace(atf,Power_pv,"Power_pv");
	//	sca_util::sca_trace(atf,SOH,"SOH");


	//sc_start(LENGTH, sc_core::SC_SEC);

	sc_start(LENGTH, sc_core::SC_SEC);

	//cout<<"Battery bank configuration is "<<batt_s<<" X "<<batt_p<<" (p x s)."<<endl;
	cout<<"The WHOLE SIMULATION LENGTH "<<"====== "<<sc_time_stamp()<<endl;
	cout<<"===================================================================="<<endl;

	//sca_util::sca_close_tabular_trace_file( atf );	

	return 0;


}
