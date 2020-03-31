#include "battery_voc.h"

void battery_voc::set_attributes(){
	out.set_timestep(SIM_STEP,sc_core::SC_SEC);
	in4.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out2.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out3.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out4.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out5.set_timestep(SIM_STEP,sc_core::SC_SEC); //SOH
}

// Pass the data from main.cpp, the data set on the command line
void battery_voc::set_data(int &batt_s, int &batt_p){
	batt_snum = batt_s;
	batt_pnum = batt_p;
}

void battery_voc::initialize(){

}


void battery_voc::processing(){
	double tmpcurrent = in.read();


	if(in4.read()==0){
	//soh = soh - 3.66e-05*exp(0.04951*abs(tmpcurrent)/batt_pnum)*exp(0.19804*abs(tmpcurrent)/batt_pnum)/86400;
	soh = soh - 3.66e-05*exp(0.04951*abs(tmpcurrent)/batt_pnum)/30000;
	}else{
	soh = 1;
	}
	tmpsoc = tmpsoc-((tmpcurrent*SIM_STEP)/((3600*3.4*batt_snum)*soh)); //Modify the capacity, 150Ah is the reference one
	//tmpsoc = tmpsoc-((tmpcurrent*SIM_STEP)/(3600*3.4*batt_snum)); //Modify the capacity, 150Ah is the reference one

	double deltacurrent = in2.read();
	double deltafrequency = in3.read();

	tmpsoc = tmpsoc - deltacurrent - deltafrequency;

	/*
	if(tmpsoc > 0.9){
		tmpsoc = 0.9;
	}
	if(tmpsoc < 0.1){
		tmpsoc = 0.1;
	}

		Battery mangagement unit: if the SOC of battery less than 10%, the battery stop to work
		if(tmpsoc<=0.1){
			cout<<"SOC is less than or equal to 10%: "<<tmpsoc<<" @"<<sc_time_stamp()<<endl;
			sc_stop();
		}

	*/

	//12V 150Ah battery
	out.write((24.56*pow(tmpsoc,5)-71.5*pow(tmpsoc,4)+78.45*pow(tmpsoc,3)-40.51*pow(tmpsoc,2)+10.23*tmpsoc+4.1)*batt_pnum);
	out2.write(0.0042*exp(-0.07909*tmpsoc)-0.0035);
	//out2.write(0.0005);
	out3.write(tmpsoc);
	out4.write(tmpsoc);
	out5.write(soh);

	if (t == LENGTH - 1) {
	cout<<"Battery bank configuration is "<<batt_snum<<" X "<<batt_pnum<<" (p x s)."<<endl;
	cout<<"===================================================================="<<endl;
	}
        t++;


}











