#include "systemc.h"
#include "simple_process_ex.h"

int sc_main(int argc, char *argv[]) {
  simple_process_ex inst("my_instance");
  sc_start();
  return 0;
}
