#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_pv){

	sca_tdf::sca_in<double> in; // Real Power get from power layer
	sca_tdf::sca_out<double> out1,out2; // Cost of pv: Aging + M&O
	
	
	
	SCA_CTOR(c_pv):in("in"),out1("out1"),out2("out2"),current_time(0),pv_aging(0.0),pv_depr(0.0),pv_mo(0.0),power(0.0) {}
	void set_data(int &pv_num);

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double mo_price, pv_cap, pv_aging, pv_mo, pv_depr;
        double current_time,power;
	int  pv_number;

};
