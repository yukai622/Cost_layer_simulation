#include "c_wt.h"

void c_wt::set_attributes(){
		in.set_timestep(SIM_STEP, sc_core::SC_SEC);
		in.set_rate(RATE);
		out1.set_timestep(RATE, sc_core::SC_SEC);
		out2.set_timestep(RATE, sc_core::SC_SEC);
}


void c_wt::initialize(){
	mo_price = 25; // The unit is /kw/year
	wt_cap = 19500; // The battery pack capital cost
}


void c_wt::processing(){

	current_time = double(sc_time_stamp().to_seconds());
//	cout<< "SImulation time now is:"<<current_time<<endl;
//

	//M&O cost
	power = 0;
	for(int i =0; i<RATE;i++){
	power = power + in.read(i);
	}

	wt_mo =wt_mo +  mo_price/31536000*power*0.001;	

	//Depreciation cost
	wt_aging = WT_NUM * wt_cap*0.094*(current_time/31536000);


	int timenow = int(current_time);

	if(timenow == (LENGTH-60)){
		cout<<"Wind turbine depreciation cost is: "<<wt_aging<<endl;
		cout<<"Wind turbine M&O cost is: "<<wt_mo<<endl;
		cout<<"==========================================="<<endl;
	}	


	out1.write(wt_aging);
	out2.write(wt_mo);

}






