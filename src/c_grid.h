#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_grid){

	//sca_tdf::sca_in<double> in; // Real Power get from power layer
	sca_tdf::sca_out<double> out; // Electricity price stepwise function 
	
	ifstream dynamicp;
	
	SCA_CTOR(c_grid):out("out"),counter(1),i(0),current_time(0) {}

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	int current_time, counter,i;
	double price[168];

};
