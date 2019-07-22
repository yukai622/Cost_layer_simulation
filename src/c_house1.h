#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_house1){

	sca_tdf::sca_in<double> in; // Real Power get from power layer
	sca_tdf::sca_out<double> out; // Electricity cost 
	
	
	SCA_CTOR(c_house1):out("out"), in("in"), counter(0) {}

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	int counter;

};
