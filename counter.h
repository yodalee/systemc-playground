#ifndef COUNTER_H_
#define COUNTER_H_ value
#include "systemc.h"

SC_MODULE(counter) {
  sc_in<bool>  start;
  sc_in<int>   limit;
  sc_out<bool> full;

  int cnt;
  void run_counter();

  SC_CTOR(counter) {
    SC_THREAD(run_counter);
    sensitive << start << limit;
    cnt = 0;
  }
};
#endif /* ifndef COUNTER_H_ */
