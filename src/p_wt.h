#include "systemc-ams.h"
#include "tstep.h"
#include "math.h"


SCA_TDF_MODULE (p_wt)
{  
  
  sca_tdf::sca_out<double> power,windspeed; 


  ifstream in_wind_speed;

  SCA_CTOR(p_wt): power("power"),wt_power(0.0), windspeed("windspeed"), counter(0), wind(0.0), wtp(0.0) {}

  void set_attributes();

  void initialize();

  void processing();

	private:
  	int counter;
	double wind;
	double wtp,wt_power;
};
