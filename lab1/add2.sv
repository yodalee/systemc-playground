module AddEveryTwoNumber (
  input clk,
  input ivalid,
  input [15:0] idata,
  output logic ovalid,
  output [15:0] odata
);

// we should have a rst here, but just ignore it
logic cnt = 0;
logic [15:0] sum;

always_ff @(posedge clk) begin
  if (ivalid) begin
    if (cnt == 1) begin
      ovalid <= 1'b1;
      odata <= idata + sum;
      sum <= 0;
      cnt <= 1'b0;
    end
    else begin
      sum <= idata + sum;
      cnt <= cnt + 1;
    end
  end

  if (ovalid == 1'b1) begin
    ovalid <= 1'b0;
  end
end

endmodule
