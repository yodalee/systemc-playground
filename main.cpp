#include "systemc.h"
#include "counter.h"
#include "drain.h"

int sc_main(int argc, char *argv[]) {
  const int kWidth = 32;
  sc_clock clk("clk", 1, SC_NS);
  sc_fifo<sc_uint<kWidth>> source(2);

  Counter<kWidth> counter_inst("my_counter");
  Counter<kWidth> counter_inst2("my_counter2");

  Drain drain_inst("my_drain");
  counter_inst.clk(clk);
  counter_inst.in(source);
  counter_inst2.clk(clk);
  counter_inst2.in(counter_inst.out);
  drain_inst.in(counter_inst2.out);
  source.write(10);

  sc_start(100, SC_US);
  return 0;
}
