#include "stdio.h"
#include "stdlib.h"
#include "p_battery.h"
#include "p_bus.h"
#include "p_pv.h"
#include "p_wt.h"
#include "battery_converter.h"
#include "pv_converter.h"
#include "wind_inverter.h"
#include "p_house1.h"
#include "p_house2.h"
#include "p_house5.h"
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

	// Pass the data from command line
	p_batt.voc->set_data(batt_s,batt_p);
	p_pv.set_data(pv_num);


	//----------------------Binding in powerlayer-----------------------
	
	//Battery
	p_batt.I(Ibatt);
	p_batt.V(Vbatt);
	p_batt.SOC(SOC);

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


	//sca_util::sca_decimation(1000);
	//To store the values during simualtion
	//sca_util::sca_trace_file* atf = sca_util::sca_create_tabular_trace_file( "trace.txt" );

	//atf->set_mode(sca_decimation(10));

	//Selecting signals to track

	//sca_util::sca_trace(atf,buy,"BUY");
	//sca_util::sca_trace(atf,sell,"SELL");

	//sca_util::sca_trace(atf,Ibatt,"Ibatt");
	//sca_util::sca_trace(atf,SOC,"SOC");
	//sca_util::sca_trace(atf,Vbatt,"Vbatt");
	//sca_util::sca_trace(atf,Phouse1,"Phouse1");
	//sca_util::sca_trace(atf,Phouse2,"Phouse2");
	//sca_util::sca_trace(atf,Phouse5,"Phouse5");
	
	//sca_util::sca_trace(atf,wind_speed,"Wind");
	//sca_util::sca_trace(atf,Iwind_inv,"Wind_current");
	//sca_util::sca_trace(atf,Ipv_cnv,"Pv_current");
	//sca_util::sca_trace(atf,Power_wind,"Power_wind");

	//sca_util::sca_trace(atf,sun_irradiance,"Sun_profile");
	//sca_util::sca_trace(atf,Power_pv,"Power_pv");

	//sc_start();


	//sc_core::sc_set_time_resolution(1.0,sc_core::SC_SEC);	
	//sc_start(LENGTH, sc_core::SC_SEC);

	sc_start(LENGTH, sc_core::SC_SEC);

        //cout<<"Battery bank configuration is "<<batt_s<<" X "<<batt_p<<" (p x s)."<<endl;
	cout<<"Report: The WHOLE SIMULATION LENGTH "<<"====== "<<sc_time_stamp()<<endl;

	//sca_util::sca_close_tabular_trace_file( atf );	

	return 0;


}
