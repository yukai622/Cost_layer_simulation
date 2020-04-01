#include "c_battery.h"

void c_battery::set_attributes(){
		in1.set_timestep(SIM_STEP, sc_core::SC_SEC);
		in2.set_timestep(SIM_STEP, sc_core::SC_SEC);
		in3.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out1.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out2.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out3.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out3.set_delay(1);
}

void c_battery::set_data(int &batt_s, int &batt_p){
	batt_snum = batt_s;
	batt_pnum = batt_p;
}

void c_battery::initialize(){
	battery_mo = 15; // The unit is /kw/year
	battery_cap = 2.5*batt_snum*batt_pnum; // The battery pack capital cost
//	lifetime = BATTLIFETIME;
}


void c_battery::processing(){

	current_time = double(sc_time_stamp().to_seconds());

	if(in3.read()>=0.8){
	batt_depr = counter * battery_cap + battery_cap*5*(1-in3.read());
	out1.write(batt_depr);
	out3.write(0);
	}else{
	batt_depr = battery_cap*(counter+1);
	out1.write(batt_depr);
	out3.write(1);
	counter++;
	}

	
	batt_mo = batt_mo + abs(in1.read())*0.001*abs(in2.read())/3153600;
//	cout<<"Time at "<<sc_time_stamp()<<"battery mo is "<<batt_mo<<endl;
//	batt_mo = batt_mo + battery_mo*power/31536000/1000000;

	out2.write(batt_mo);


	if(count == (LENGTH-1)){
		cout<<"Battery pack depreciation cost is: "<<batt_depr<<endl;
		cout<<"Battery pack M&O cost is: "<<batt_mo<<endl;
		cout<<"===================================================================="<<endl;
	
	}


	count = count + 1;

}






