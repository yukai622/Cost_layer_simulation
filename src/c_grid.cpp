#include "c_grid.h"

void c_grid::set_attributes(){
	//	in.set_timestep(SIM_STEP, sc_core::SC_SEC);
		out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void c_grid::initialize(){

	dynamicp.open("../one_year_inputs/dynamicprice.txt");

	if(!dynamicp){
		cout<<"Cannot open dynamic price!"<<endl;
		exit(-1);
	}

	for(int j=0; j<168;j++){
		dynamicp >> price[j];
	}

	dynamicp.close();

}



void c_grid::processing(){

	//current_time = int(sc_time_stamp().to_seconds())%86400;

	if(counter%3600 == 0 || counter == 1){
	 	i++;
		out.write(price[i-1]);
		
	}else{
		out.write(price[i-1]);
	}

	counter++;

	if(counter % 604800 == 0){
		i = 0;
	}

//	out.write(0.2);
}






