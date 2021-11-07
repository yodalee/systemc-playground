
#include "Vadd23.h"
#include <memory>
#include <systemc>

using namespace sc_core;

void Checker1(uint32_t data) {
  static size_t idx = 0;
  std::vector<uint32_t> ans = {3, 7, 11};
  assert(data == ans[idx++]);
}

void Checker2(uint32_t data) {
  static size_t idx = 0;
  std::vector<uint32_t> ans = {6, 15};
  assert(data == ans[idx++]);
}

SC_MODULE(TbAdd23) {
  // connect wire
  Vadd23 top_;
  sc_clock clk_;
  sc_signal<bool> ivalid_;
  sc_signal<uint32_t> idata_;

  sc_signal<bool> o1valid_;
  sc_signal<uint32_t> o1data_;
  sc_signal<bool> o2valid_;
  sc_signal<uint32_t> o2data_;

  void Driver();
  void Monitor();

  SC_HAS_PROCESS(TbAdd23);

  TbAdd23(sc_module_name name):
    top_("top"), clk_("clk", 1, SC_NS) {
      top_.clk(clk_);
      top_.ivalid(ivalid_);
      top_.idata(idata_);
      top_.o1valid(o1valid_);
      top_.o1data(o1data_);
      top_.o2valid(o2valid_);
      top_.o2data(o2data_);
      SC_THREAD(Driver);
      SC_THREAD(Monitor);
    }
};

void TbAdd23::Driver() {
  std::vector<uint16_t> in = {1, 2, 3, 4, 5, 6};
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

void TbAdd23::Monitor() {
  std::vector<uint16_t> ans2 = {6, 15};
  int i = 0;
  int j = 0;
  while (true) {
    wait(clk_.posedge_event());
    if (o1valid_) {
      Checker1(o1data_);
    }
    if (o2valid_) {
      Checker2(o2data_);
    }
  }
}

int sc_main(int argc, char *argv[])
{
  std::unique_ptr<TbAdd23> tb { new TbAdd23("tb_add23") };
  sc_start(100, SC_NS);
  return 0;
}
