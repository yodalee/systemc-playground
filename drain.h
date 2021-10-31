#ifndef DRAIN_H_
#define DRAIN_H_ value

#include <systemc>

SC_MODULE(Drain) {
  sc_fifo_in<int> in;

  void drain() {
    while (true) {
      auto val = in.read();
      std::cout << "Output: " << val << std::endl;
    }
  };

  SC_CTOR(Drain) {
    SC_THREAD(drain);
  }
};

#endif /* ifndef DRAIN_H_ */
