.SUFFIXES:
.SUFFIXES: .cc .cpp .o .x

CC = g++
OPT =
DEBUG = 
OTHER = -Wall -O3

# Use this CFLAGS definition if you need to see debug output
# CFLAGS = -c -g -Wno-deprecated -Wall -D_DEBUG
	#../src/turbine.cpp ../src/environment.cpp \
	#../src/aerodynamic.cpp ../src/generator.cpp \
	#../src/mechanical.cpp ../src/mechanical_tdf.cpp \
	#../src/mechanical_lsf.cpp ../src/generator_Te.cpp \
	#../src/generator_lsf.cpp ../src/generator_eq.cpp \
	#../src/wind_turbine.cpp ../src/mechanical_delay.cpp 

CFLAGS = -c -g -Wno-deprecated 

MODULE = run
SRCS =  ../src/battery_voc.cpp ../src/battery_converter.cpp ../src/battery_char.cpp ../src/battery_nonideal.cpp ../src/p_battery.cpp \
	../src/c_battery.cpp ../src/c_pv.cpp ../src/c_wt.cpp \
	../src/p_pv.cpp ../src/pv_converter.cpp \
	../src/p_wt.cpp ../src/wind_inverter.cpp \
	../src/p_house1.cpp ../src/p_house2.cpp ../src/p_house5.cpp \
	../src/c_house1.cpp ../src/c_house2.cpp ../src/c_house5.cpp \
 	../src/p_bus.cpp ../src/c_bus.cpp \
 	../src/c_grid.cpp \
	../src/main.cpp


OBJS = $(SRCS:../src/%.cpp=%.o)

include Makefile.defs
