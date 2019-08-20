#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_pv){

	//sca_tdf::sca_in<double> in; // Real Power get from power layer
	sca_tdf::sca_out<double> out; // Cost of pv: Aging + M&O
	
	
	SCA_CTOR(c_pv):out("out"),  current_time(0) {}

	void set_data(int &pv_num);

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double pv_mo, pv_cap, current_time, lifetime;
	int  pv_number;

};
