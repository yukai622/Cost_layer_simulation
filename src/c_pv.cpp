#include "c_pv.h"

void c_pv::set_attributes(){
	//	in.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_pv::set_data(int &pv_num){
	pv_number = pv_num;
}

void c_pv::initialize(){
	pv_mo = 25; // The unit is /kw/year
	pv_cap = 300*pv_number; // The battery pack capital cost
	lifetime = PVLIFETIME;
}


void c_pv::processing(){

	current_time = double(sc_time_stamp().to_seconds());
//	cout<< "SImulation time now is:"<<current_time<<endl;

	out.write(pv_mo*(current_time/31536000) + pv_cap*(current_time/lifetime));


}






