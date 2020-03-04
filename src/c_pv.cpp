#include "c_pv.h"

void c_pv::set_attributes(){
//	in.set_timestep(SIM_STEP, sc_core::SC_SEC);// Read power from power layer PV unit
	out1.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out2.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_pv::set_data(int &pv_num){
	pv_number = pv_num;
}

void c_pv::initialize(){
	mo_price = 25; // The unit is /kw/year
	pv_cap = 675*pv_number; // The PV array capital cost
}


void c_pv::processing(){

	current_time = double(sc_time_stamp().to_seconds());

	//cout<< "Simulation time now is:"<<current_time<<endl;

	//Wearout cost
	//pv_aging = pv_cap*(current_time/PVLIFETIME);

	//Depretion cost
	pv_depr = pv_cap*0.094*(current_time/31536000);

	//M&O cost
	pv_mo = mo_price*0.001*pv_number*312*(current_time/31536000);

/*
	if(current_time == (LENGTH-1)){
		cout<<"PV array depreciation cost is: "<<pv_depr<<endl;
		cout<<"PV array M&O cost is: "<<pv_mo<<endl;
		cout<<"===================================================================="<<endl;	
	}
*/
	out1.write(pv_depr);
	out2.write(pv_mo);

}






