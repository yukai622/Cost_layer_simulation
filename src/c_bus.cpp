#include "c_bus.h"

void c_bus::set_attributes(){
	c_h1.set_timestep(SIM_STEP, sc_core::SC_SEC);
	c_h2.set_timestep(SIM_STEP, sc_core::SC_SEC);
	c_h5.set_timestep(SIM_STEP, sc_core::SC_SEC);
	sell.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_bus::initialize(){
}


void c_bus::processing(){

	tmp_sell = sell.read();

	total_ele_cost = total_ele_cost + c_h1.read() + c_h2.read() + c_h5.read() - tmp_sell/3600000*0.1;


	out.write(total_ele_cost);
}






