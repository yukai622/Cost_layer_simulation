#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(inverter_wt)
{
	sca_tdf::sca_out<double> I; // Current connect to the cti bus = Power/Vbus
	sca_tdf::sca_in<double> Pwind; //Power generated from wind


	SCA_CTOR(inverter_wt): I("I"), Pwind("Pwind") {}

	void set_attributes();

	void initialize();

	void processing();
};
