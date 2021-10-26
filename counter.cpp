#include "counter.h"

void counter::run_counter() {
  while (true) {
    if (start) {
      cnt = 0;
    } else {
      if (cnt < limit) {
        cnt++;
      }
    }
    full = (cnt == limit);
    std::cout << "counter: " << cnt << " full: " << full << std::endl;
    wait(1, SC_NS);
  }
}
