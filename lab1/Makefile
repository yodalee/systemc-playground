

ARG = --sc --build --trace

all: add2 add23

add2: tb_add2.cpp
	verilator -sv add2.sv --exe tb_add2.cpp $(ARG)

add23: tb_add23.cpp
	verilator -sv add23.sv --exe tb_add23.cpp $(ARG)
