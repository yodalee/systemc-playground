#include "Vfifo.h"

#include <systemc>
#include <memory>
#include "verilated.h"

using namespace sc_core;

SC_MODULE(Testbench) {
  sc_clock clk;
  sc_signal<bool> n_rst;
  sc_signal<bool> src_valid;
  sc_signal<bool> src_ready;
  sc_signal<unsigned> src_data;

  sc_signal<bool> dest_valid;
  sc_signal<bool> dest_ready;
  sc_signal<unsigned> dest_data;

  void Reset();
  void Reader();
  void Writer();
  void Monitor();
public:
  SC_HAS_PROCESS(Testbench);
  Testbench(
      const sc_module_name& name,
      Vfifo *dut
  ): sc_module(name), clk("clk", 1, SC_NS) {
    dut->clk(clk);
    dut->n_rst(n_rst);
    dut->i_valid(src_valid);
    dut->i_ready(src_ready);
    dut->i_data(src_data);
    dut->o_valid(dest_valid);
    dut->o_ready(dest_ready);
    dut->o_data(dest_data);

    SC_THREAD(Reset);
    SC_THREAD(Writer);
    SC_THREAD(Reader);
    SC_METHOD(Monitor);
    sensitive << src_valid << src_ready << dest_valid << dest_ready;
  }
};

void Testbench::Reset() {
  n_rst.write(true);
  wait(5.0, SC_NS);
  n_rst.write(false);
  wait(5.0, SC_NS);
  n_rst.write(true);
  std::cout << "[" << sc_time_stamp() << "] Init: src_ready: " << src_ready.read() << std::endl;
  std::cout << "[" << sc_time_stamp() << "] Init: dest_valid: " << dest_valid.read() << std::endl;
}

void Testbench::Reader() {
  dest_ready.write(true);
  while (true) {
    wait(clk.posedge_event());
    if (dest_valid.read()) {
      auto val = dest_data.read();
      std::cout << "[" << sc_time_stamp() << "] Received data: " << val << std::endl;
    }
  }
}

void Testbench::Writer() {
  wait(12, SC_NS);
  src_valid.write(true);
  int i;
  for (int i = 0; i < 16; ++i) {
    wait(clk.negedge_event());
    src_data.write(i);
  }
  wait(clk.negedge_event());
  src_valid.write(false);
}

void Testbench::Monitor() {
  std::cout << "[" << sc_time_stamp() << "] (sv, sr, dv, dr) = ("
    << src_valid << " " << src_ready << " "
    << dest_valid << " " << dest_ready << ")" << std::endl;
}

int sc_main(int argc, char *argv[])
{
  std::unique_ptr<Vfifo> dut (new Vfifo("fifo"));
  std::unique_ptr<Testbench> tb (new Testbench("testbench", dut.get()));

  sc_start(100, SC_NS);
  return 0;
}
