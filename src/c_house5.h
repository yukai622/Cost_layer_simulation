#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE(c_house5){

	sca_tdf::sca_in<double> power, price, buy; 
	sca_tdf::sca_out<double> out; // Electricity cost 
	
	
	SCA_CTOR(c_house5):out("out"), price("price"),buy("buy"), power("power"), current_price(0.0), total_buy(0.0) {}

	void set_attributes();
	
	void initialize();

	void processing();
	
	private:
	double current_price,current_power,total_buy;

};
