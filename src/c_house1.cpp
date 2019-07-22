#include "p_house1.h"

void p_house1::set_attributes(){
	in.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void p_house1::initialize(){
}


void p_house1::processing(){

	
	out.write(6*rp/0.95);


}






