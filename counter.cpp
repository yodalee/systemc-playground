#include "counter.h"

void Counter::run_counter() {
  while (true) {
    int val = in->read();
    std::cout << "val: " << val << std::endl;
    for (int cnt = 0; cnt < val; ++cnt) {
      out->write(cnt);
      wait(1, SC_NS);
    }
  }
}
