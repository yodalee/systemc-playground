module Fifo (
  input clk,
  input n_rst,

  // input interface
  input i_valid,
  output i_ready,
  input [DATA_WIDTH-1:0] i_data,

  // output interface
  input o_ready,
  output o_valid,
  output [DATA_WIDTH-1:0] o_data
);

parameter DATA_WIDTH = 32;
parameter BUF_SIZE = 2;

reg [DATA_WIDTH-1:0] data;
reg has_data;

always_ff @(posedge clk) begin
  if (!n_rst) begin
    data <= 0;
    has_data <= 1'b0;
  end
  else begin
    if (i_valid && i_ready && ~o_ready) begin
      data <= i_data;
      has_data <= 1'b1;
    end
    else if (o_valid && o_ready) begin
      has_data <= 1'b0;
    end
  end
end

assign i_ready = ~has_data;
assign o_valid = has_data || (~has_data && i_valid);
assign o_data = (i_valid && i_ready && o_ready) ? i_data : data;

endmodule
