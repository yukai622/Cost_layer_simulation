#include "c_grid.h"

void c_grid::set_attributes(){
	//	in.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_grid::initialize(){
}


void c_grid::processing(){

	current_time = int(sc_time_stamp().to_seconds())%86400;

	if(current_time<= 25200){
	out.write(0.2);
	}else if(current_time <= 68400){
	out.write(0.215);
	}else if(current_time <= 82800){
	out.write(0.22);
	}else{
	out.write(0.2);
	}


}






