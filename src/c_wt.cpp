#include "c_wt.h"

void c_wt::set_attributes(){
	//	in.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}


void c_wt::initialize(){
	wt_mo = 25; // The unit is /kw/year
	wt_cap = 10000; // The battery pack capital cost
	lifetime = WTLIFETIME;
}


void c_wt::processing(){

	current_time = double(sc_time_stamp().to_seconds());
//	cout<< "SImulation time now is:"<<current_time<<endl;

	out.write(wt_mo*(current_time/31536000) + wt_cap*(current_time/lifetime));


}






