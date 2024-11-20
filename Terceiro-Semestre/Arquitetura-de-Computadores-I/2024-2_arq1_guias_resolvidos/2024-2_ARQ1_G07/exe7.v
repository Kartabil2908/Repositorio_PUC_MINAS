module teste_magnitude (
    output reg s_out,
    input [2:0] a,
    input [2:0] b,
    input select
);

  wire a_gt_b, a_lt_b;

  assign a_gt_b = (a[2] & ~b[2]) | ((a[2] == b[2]) & (a[1] & ~b[1])) | ((a[2] == b[2]) & (a[1] == b[1]) & (a[0] & ~b[0]));
  assign a_lt_b = (~a[2] & b[2]) | ((a[2] == b[2]) & (~a[1] & b[1])) | ((a[2] == b[2]) & (a[1] == b[1]) & (~a[0] & b[0]));

  always @(*) begin
    if (select == 1'b0) begin
      s_out = a_lt_b; // a < b
    end else begin
      s_out = a_gt_b; // a > b
    end
  end

endmodule

// Módulo de teste
module test_teste_magnitude;
  reg [2:0] a, b;
  reg select;
  wire s_out;

  teste_magnitude dut (
    .s_out(s_out),
    .a(a),
    .b(b),
    .select(select)
  );

  initial begin
    $display("Teste de comparação de Magnitude");
    $display(" a b select s_out");

    a = 3'b101; b = 3'b101; select = 1'b0;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 a = 3'b010; b = 3'b101;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 1'b1;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 $finish;
  end
endmodule