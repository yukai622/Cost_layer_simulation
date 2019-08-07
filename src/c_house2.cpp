#include "c_house2.h"

void c_house2::set_attributes(){
	power.set_timestep(SIM_STEP, sc_core::SC_SEC);
	price.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_house2::initialize(){
}


void c_house2::processing(){

	
	current_price = price.read();

	out.write(current_price*current_price/3600000);


}






