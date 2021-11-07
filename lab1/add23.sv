module AddEveryTwoNumber (
  input clk,
  input ivalid,
  input [15:0] idata,
  output logic o1valid,
  output [15:0] o1data,
  output logic o2valid,
  output [15:0] o2data
);

// we should have a rst here, but just ignore it
logic cnt1 = 0;
logic [15:0] sum1;

logic [1:0] cnt2 = 0;
logic [15:0] sum2;

always_ff @(posedge clk) begin
  if (ivalid) begin
    if (cnt1 == 1) begin
      sum1 <= 0;
      cnt1 <= 0;
      o1valid <= 1'b1;
      o1data <= idata + sum1;
    end
    else begin
      sum1 <= idata + sum1;
      cnt1 <= cnt1 + 1;
    end

    if (cnt2 == 2) begin
      sum2 <= 0;
      cnt2 <= 0;
      o2valid <= 1'b1;
      o2data <= idata + sum2;
    end
    else begin
      sum2 <= idata + sum2;
      cnt2 <= cnt2 + 1;
    end
  end

  if (o1valid) begin
    o1valid <= 1'b0;
  end
  if (o2valid) begin
    o2valid <= 1'b0;
  end
end

endmodule
