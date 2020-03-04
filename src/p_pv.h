#include "systemc-ams.h"
#include "tstep.h"


SCA_TDF_MODULE (p_pv)
{ 

  sca_tdf::sca_out<double> P; 
  sca_tdf::sca_out<double> sun_irradiance; 

  double Gtop, Gwest;// Define in tstep.h 

  ifstream top; // To store the irradiance profile

  SCA_CTOR(p_pv): P("P"), sun_irradiance("sun_irradiance"), Ptop(0), Pback(0),counter(0) {}


  int pv_number;
  void set_data(int &pv_num);
  void set_attributes();

  void initialize();

  void processing();


  private:
  int counter,pv_num;
  double Ptop, Pback;

};
