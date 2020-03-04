#include "c_battery.h"

void c_battery::set_attributes(){
	//	in.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out1.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out2.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_battery::set_data(int &batt_s, int &batt_p){
	batt_snum = batt_s;
	batt_pnum = batt_p;
}

void c_battery::initialize(){
	battery_mo = 15; // The unit is /kw/year
	battery_cap = 2.5*batt_snum*batt_pnum; // The battery pack capital cost
	lifetime = BATTLIFETIME;
}


void c_battery::processing(){

	current_time = double(sc_time_stamp().to_seconds());
	//cout<< "SImulation time now is:"<<current_time<<endl;

	out1.write(battery_cap*(current_time/lifetime));
	out2.write(battery_mo*(current_time/31536000));

	/*
	cout<<battery_mo*(current_time/31536000)<<endl;
	cout<<(current_time/31536000)<<endl;
	cout<<battery_cap*(current_time/lifetime)<<endl;
	cout<<current_time/lifetime<<endl;
	cout<<(lifetime)<<endl;
	*/

}






