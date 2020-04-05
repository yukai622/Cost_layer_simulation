#include "p_wt.h"

void p_wt::set_attributes()
{
	power.set_timestep(SIM_STEP, sc_core::SC_SEC);
	//P.set_delay(1);
}

void p_wt::initialize()
{
	in_wind_speed.open("../one_year_inputs/one_year_wind_new.txt"); // _new for full exploration

	if (!in_wind_speed) {
		cout << "Cannot open file.\n"<< endl;
		exit(-1);
	}


}


void p_wt::processing()
{  

	//double wind_high;

	if(counter%600 == 0){ // Determined by the time step of trace	
		in_wind_speed >> wind;
		//wind_high = wind*(log(50/0.3)/log(3/0.3)); // Notice the height of wind spedd
	}

	//double wtp; 

	//cout<<wind<<"@"<<sc_time_stamp()<<endl; 

	//wind = wind + 10;
	//wtp =(11200*sin(0.15628*wind-0.623) + 2015*sin(0.6514*wind+0.2421))*0.788; 
	//time 8 for south exploration, time 10 for north
	wtp = 1.056 * WT_NUM *((12570*exp(-pow((wind-17.1)/7.068,2))+5762*exp(-pow((wind-10.88)/3.319,2)))*0.72+200); // for increase wind speed for 50m height. The times 1.05 for the big plot in the energies paper.


	wt_power = wt_power + wtp;
	//cout << wtp << sc_time_stamp()<<endl;
	
	power.write(wtp); 

	windspeed.write(wind);


	if (counter == LENGTH - 1) {
		cout<<"===================================================================="<<endl;
		cout<<"Wind Turbine works well until to the "<<sc_time_stamp()<<endl;
		cout<<"The total wind power generation is "<<wt_power*0.001<<endl;
		cout<<"===================================================================="<<endl;
		//cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
		in_wind_speed.close();
	}

	counter++;

}

