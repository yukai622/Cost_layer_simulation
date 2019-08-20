#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_wt){

	//sca_tdf::sca_in<double> in; // Real Power get from power layer
	sca_tdf::sca_out<double> out; // Cost of pv: Aging + M&O
	
	
	SCA_CTOR(c_wt):out("out"),  current_time(0) {}


	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double wt_mo, wt_cap, current_time, lifetime;

};
