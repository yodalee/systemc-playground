#include "systemc.h"
#include "counter.h"
#include "drain.h"

int sc_main(int argc, char *argv[]) {
  sc_fifo<int> source(1);
  sc_fifo<int> drain(1);
  Counter counter_inst("my_counter");
  Drain drain_inst("my_drain");
  counter_inst.in(source);
  counter_inst.out(drain);
  drain_inst.in(drain);
  source.write(10);

  sc_start(100, SC_US);
  return 0;
}
