#include "c_house5.h"

void c_house5::set_attributes(){
	power.set_timestep(SIM_STEP, sc_core::SC_SEC);
	price.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_house5::initialize(){
}


void c_house5::processing(){

	
	current_price = price.read();
	current_power = power.read();
	total_buy = buy.read();

	if(total_buy>0){
//	out.write(-current_power*current_price/3600000);
	out.write(-total_buy/3*current_price/3600000);
	}else{
	out.write(current_power*current_price/3600000);
	}
	


}






