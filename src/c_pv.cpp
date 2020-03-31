#include "c_pv.h"

void c_pv::set_attributes(){
	in.set_timestep(SIM_STEP, sc_core::SC_SEC);// Read power from power layer PV unit
	in.set_rate(RATE);
	out1.set_timestep(RATE, sc_core::SC_SEC);
	out2.set_timestep(RATE, sc_core::SC_SEC);
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
	pv_depr = pv_cap*0.094*(current_time/31536000); //CRF is 0.094

	//M&O cost
	//pv_mo = mo_price*0.001*pv_number*in.read()*(current_time/31536000);
	//

	power = 0;
	for(int i=0;i<RATE;i++){
		power = power + in.read(i);
		//	cout<<"The"<< i<<"th read power is " << in.read(i)<<endl;
	}

	pv_mo = pv_mo + mo_price*power*0.001/525600;


	//	cout<<"PV deperiation cost is "<< pv_depr <<" PV m&o cost is "<<pv_mo<<endl;


	//	int timenow = int(current_time);

	if(counter == (LENGTH-60)){
		cout<<"PV array depreciation cost is: "<<pv_depr<<endl;
		cout<<"PV array M&O cost is: "<<pv_mo<<endl;
		cout<<"===================================================================="<<endl;	
	}

	out1.write(pv_depr);
	out2.write(pv_mo);

	counter = counter + 60;
	//cout<<counter<<endl;
}






