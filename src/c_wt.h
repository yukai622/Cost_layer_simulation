#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_wt){

	sca_tdf::sca_in<double> in; // Rate Power get from power layer
	sca_tdf::sca_out<double> out1,out2; // Cost of pv: Aging + M&O
	
	
	SCA_CTOR(c_wt):in("in"),out1("out1"),out2("out2"),current_time(0) {}


	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double mo_price,wt_mo,wt_cap,wt_aging;
	double current_time;

};
