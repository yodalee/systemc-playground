#ifndef COUNTER_H_
#define COUNTER_H_ value
#include <systemc.h>

SC_MODULE(Counter) {
  sc_fifo_in<int> in;
  sc_port<sc_fifo_out_if<int>> out;

  void run_counter();

  SC_CTOR(Counter) {
    SC_THREAD(run_counter);
  }
};
#endif /* ifndef COUNTER_H_ */
