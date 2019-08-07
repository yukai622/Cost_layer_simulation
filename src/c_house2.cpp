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
	current_power = power.read();

	if(buy.read()>0){
	out.write(-current_power*current_price/3600000);
	}else{
	out.write(current_power*current_price/3600000);
	}


}






