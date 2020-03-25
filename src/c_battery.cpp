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
	//cout<< "SImulation time now is:"<<current_time<<endl;

	if(in3.read()>=0.8){
	out1.write(counter*battery_cap + battery_cap*5*(1-in3.read()));
	out3.write(0);
	}else{
	out1.write(battery_cap*(counter+1));
	out3.write(1);
	counter++;
	}

	
	power = power + abs(in1.read())*abs(in2.read());

	out2.write(battery_mo*power*0.001/31536000);

	/*
	cout<<battery_mo*(current_time/31536000)<<endl;
	cout<<(current_time/31536000)<<endl;
	cout<<battery_cap*(current_time/lifetime)<<endl;
	cout<<current_time/lifetime<<endl;
	cout<<(lifetime)<<endl;
	*/

}






