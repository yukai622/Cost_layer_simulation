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
//	cout<< "Simulation time now is:"<<current_time<<endl;

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

	
	power = power + abs(in1.read())*0.001*abs(in2.read())/86400;
	//cout<<power<<endl;
	batt_mo = batt_mo + battery_mo*power/31536000;

	out2.write(batt_mo);

	int timenow = int(current_time);

//	cout<<timenow<<endl;

	if(count == (LENGTH-1)){
		cout<<"Battery pack depreciation cost is: "<<batt_depr<<endl;
		cout<<"Battery pack M&O cost is: "<<batt_mo<<endl;
		cout<<"===================================================================="<<endl;
	
	}


	count = count + 1;
	//cout << count << endl;
	/*
	cout<<battery_mo*(current_time/31536000)<<endl;
	cout<<(current_time/31536000)<<endl;
	cout<<battery_cap*(current_time/lifetime)<<endl;
	cout<<current_time/lifetime<<endl;
	cout<<(lifetime)<<endl;
	*/

}






