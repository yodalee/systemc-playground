#include "simple_process_ex.h"
#include <iostream>

void simple_process_ex::my_thread_process(void)
{
  wait(10, SC_NS);
  std::cout << "Now at " << sc_time_stamp() << std::endl;
  sc_time t_DELAY(2, SC_MS);
  wait(t_DELAY);
  std::cout << "Now at " << sc_time_stamp() << std::endl;
}
