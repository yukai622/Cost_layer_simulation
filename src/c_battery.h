#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_battery){

	//sca_tdf::sca_in<double> in; // Real Power get from power layer
	sca_tdf::sca_out<double> out1,out2; // Electricity price stepwise function 
	
	
	SCA_CTOR(c_battery):out1("out1"),out2("out2"),current_time(0) {}

	void set_data(int &batt_s, int &batt_p);

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double battery_mo, battery_cap, current_time, lifetime;
	int  batt_snum, batt_pnum;

};
