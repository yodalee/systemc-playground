
ARG = --sc --build --trace
ALL: fifo

fifo: fifo.sv tb_fifo.cpp
	verilator -sv fifo.sv --exe tb_fifo.cpp $(ARG)
