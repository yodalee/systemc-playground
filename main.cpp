#include "systemc.h"
#include "counter.h"

int sc_main(int argc, char *argv[]) {
  sc_signal<int> limit("limit", 90);
  sc_signal<bool> start, full;
  counter counter_inst("my_counter");
  counter_inst(start, limit, full);

  sc_start(100, SC_NS);
  return 0;
}
