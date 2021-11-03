#ifndef COUNTER_H_
#define COUNTER_H_ value
#include <systemc.h>

template<int kWidth = 32>
SC_MODULE(Counter) {
  sc_in<bool> clk;
  sc_fifo_in<sc_uint<kWidth>> in;
  sc_fifo<sc_uint<kWidth>> out;

  void run_counter() {
    while (true) {
      int val = in->read();
      std::cout << "val: " << val << std::endl;
      for (int cnt = 0; cnt < val; ++cnt) {
        out.write(cnt);
        wait(1, SC_NS);
      }
    }
  };

  SC_CTOR(Counter) {
    SC_THREAD(run_counter);
    sensitive << clk.pos();
  }
};
#endif /* ifndef COUNTER_H_ */
