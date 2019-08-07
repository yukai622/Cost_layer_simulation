#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_bus){

	sca_tdf::sca_in<double> c_h1,c_h2,c_h5; // Cost of different load
	sca_tdf::sca_in<double> sell; // buy already considered in different loads
	sca_tdf::sca_out<double> out; // Total benefit
	
	
	SCA_CTOR(c_bus):out("out"), sell("sell"), c_h1("c_h1"), c_h2("c_h2"), c_h5("c_h5"), total_ele_cost(0.0), total_mo_cost(0.0) {}

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double total_ele_cost, total_mo_cost, tmp_sell;

};
