#include <systemc>

using namespace sc_core;
SC_MODULE(Module1) {
  sc_signal<int> s;
  sc_port<sc_signal_out_if<int>> p;

  SC_CTOR(Module1) {
    SC_THREAD(selfWrite);
    SC_THREAD(selfRead);
    sensitive << s;
    dont_initialize();
    SC_THREAD(outsideWrite);
  }

  void selfWrite() {
    int val = 0;
    while (true) {
      s.write(val++);
      wait(1, SC_NS);
    }
  }

  void selfRead()
  {
    while (true) {
      std::cout << sc_time_stamp() << " : read from channel, val = " << s.read() << std::endl;
      wait();
    }
  }

  void outsideWrite() {
    int val = -1;
    while (true) {
      p->write(val--);
      wait(5, SC_NS);
    }
  }
};

SC_MODULE(Module2) {
  sc_port<sc_signal_in_if<int>> p;
  SC_CTOR(Module2) {
    SC_THREAD(outsideRead);
    sensitive << p;
    dont_initialize();
  }

  void outsideRead()
  {
    while (true) {
      std::cout << sc_time_stamp() << " : read from outside channel, val = " << p->read() << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char *argv[])
{
  Module1 module1("module1");
  Module2 module2("module2");
  sc_signal<int> s;
  module1.p(s);
  module2.p(s);
  sc_start(15, SC_NS);
  return 0;
}
