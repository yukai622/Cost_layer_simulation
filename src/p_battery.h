#include "systemc-ams.h"
#include "battery_char.h"
#include "battery_voc.h"
#include "battery_nonideal.h"



SC_MODULE(p_battery){
	// interface and internal components declaration
	sca_tdf::sca_in<double> I; // Ib current
	//	sca_tdf::sca_in<int> snum; // s number
	//	sca_tdf::sca_in<int> pnum; // p number
	sca_tdf::sca_out<double> V; // Vb battery voltage
	sca_tdf::sca_out<double> SOC; //SOC
	sca_tdf::sca_out<double> SOH; //SOH


	//Connecting signals
	sca_tdf::sca_signal<double> Voc, Rs, deltaf, deltac, tmpsoc;

	//Instantiation of battery componenets
	battery_voc* voc;
	battery_char* batt;
	battery_nonideal* nonideal;

	SC_CTOR(p_battery): I("I"),V("V"),SOC("SOC")
	{

		voc = new battery_voc("voc");
		batt = new battery_char("batt");
		nonideal = new battery_nonideal("nonideal");

		voc->in(I);
		voc->in2(deltac);
		voc->in3(deltaf);
		//		voc->in4(snum);
		//		voc->in5(pnum);
		voc->out(Voc);
		voc->out2(Rs);
		voc->out3(SOC);
		voc->out4(tmpsoc);
		voc->out5(SOH);

		batt->in(Rs);
		batt->in2(I);
		batt->in3(Voc);
		batt->out(V);

		nonideal->in(I);
		nonideal->in2(tmpsoc);
		nonideal->out(deltac);
		nonideal->out2(deltaf);
	}

};








