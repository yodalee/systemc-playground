

ARG = --sc --build --trace

all: add2

add2: tb_add2.cpp
	verilator -sv add2.sv --exe tb_add2.cpp $(ARG)
