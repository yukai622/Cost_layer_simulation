#include "c_house1.h"

void c_house1::set_attributes(){
	power.set_timestep(SIM_STEP, sc_core::SC_SEC);
	price.set_timestep(SIM_STEP, sc_core::SC_SEC);
	buy.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_house1::initialize(){
}


void c_house1::processing(){

	
	current_price = price.read();
	current_power = power.read();
	total_buy = buy.read();


	if(total_buy>0){
//	out.write(-current_power*current_price/3600000);// if buy power from grid, the house lose money, so there is negative
	out.write(-total_buy/3*current_price/3600000);// if buy power from grid, the house lose money, so there is negative
	}else{
	out.write(current_power*current_price/3600000); // this is positive since do not need to buy, the house get profit
	}


}






