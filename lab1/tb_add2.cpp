
#include "Vadd2.h"
#include <memory>
#include <systemc>

using namespace sc_core;

SC_MODULE(TbAdd2) {
  // testdata
  std::vector<uint16_t> in = {1, 2, 3, 4, 5, 6};
  std::vector<uint16_t> ans = {3, 7, 11};

  // connect wire
  Vadd2 top_;
  sc_clock clk_;
  sc_signal<bool> ivalid_;
  sc_signal<uint32_t> idata_;

  sc_signal<bool> ovalid_;
  sc_signal<uint32_t> odata_;

  void Driver();
  void Monitor();

  SC_HAS_PROCESS(TbAdd2);

  TbAdd2(sc_module_name name):
    top_("top"), clk_("clk", 1, SC_NS) {
      top_.clk(clk_);
      top_.ivalid(ivalid_);
      top_.idata(idata_);
      top_.ovalid(ovalid_);
      top_.odata(odata_);
      SC_THREAD(Driver);
      SC_THREAD(Monitor);
    }
};

void TbAdd2::Driver() {
  ivalid_.write(0);
  wait(clk_.posedge_event());
  for (int i = 0; i < 6; ++i) {
    wait(clk_.posedge_event());
    ivalid_.write(true);
    idata_.write(in[i]);
  }
  wait(clk_.posedge_event());
  ivalid_.write(0);
}

void TbAdd2::Monitor() {
  int i = 0;
  while (true) {
    wait(clk_.posedge_event());
    if (ovalid_) {
      assert(odata_ == ans[i++]);
    }
  }
}

int sc_main(int argc, char *argv[])
{
  std::unique_ptr<TbAdd2> tb { new TbAdd2("tb_add2") };
  sc_start(100, SC_NS);
  return 0;
}
