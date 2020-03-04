#include "p_pv.h"

void p_pv::set_attributes()
{
	P.set_timestep(SIM_STEP, sc_core::SC_SEC);
	sun_irradiance.set_timestep(SIM_STEP, sc_core::SC_SEC);
	//P.set_delay(1);
}


void p_pv::set_data(int &pv_num){

pv_number = pv_num;

}

void p_pv::initialize()
{
	//unsigned int i;
	//ifstream top, back; 

	top.open("../one_year_inputs/one_year_sun_south.txt"); 
	if (!top) {
		cout << "Cannot open irradiance file.\n"<< endl;
		exit(-1);
	}

}


void p_pv::processing()
{  


	if(counter%60 == 0.0){
		top >> Gtop;
		Gwest = Gtop;
	}

	//cout<<Gtop<<"@"<<sc_time_stamp()<<endl;

	// Original equations
	//  Ptop = 4.752e-09*pow(Gtop,3) - 7.352e-06*pow(Gtop,2) + 0.02238*Gtop - 0.6954; 
	//  Pback = 4.752e-09*pow(Gwest,3) - 7.352e-06*pow(Gwest,2) + 0.02238*Gwest - 0.6954;

	// Avoid negative power value during night, actually this is correct
	// We can use this negative value to represent power consumption of PV if reviewer argure this point
	Ptop = 4.752e-09*pow(Gtop,3) - 7.352e-06*pow(Gtop,2) + 0.02238*Gtop; 
	Pback = 4.752e-09*pow(Gwest,3) - 7.352e-06*pow(Gwest,2) + 0.02238*Gwest;




	if (Ptop < 0){
		P.write(0);
	}else{  

		P.write((Ptop + Pback)*7.5 * pv_number );// One Ptop + Pback is 300W 

	}

	sun_irradiance.write(Gtop);



	if (counter == LENGTH-1) {
		cout<<"Report: PV panel works correctly until to the "<<sc_time_stamp()<<endl;
		cout<<"===================================================================="<<endl;
//		cout<<"PV array has " <<pv_number <<" panels! "<<"@"<<sc_time_stamp()<<endl;
		cout<<"PV array has " <<pv_number <<" panels! "<<endl;
//		cout<<"===================================================================="<<endl;

		top.close();

	}

	counter++;

}

