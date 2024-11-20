module lu_advanced_xor_xnor (
    output reg s_out,
    input a,
    input b,
    input [1:0] select
);

  always @(*) begin
    case (select)
      2'b00: s_out = ~(a | b); // NOR
      2'b01: s_out = a | b; // OR
      2'b10: s_out = a ^ b; // XOR
      2'b11: s_out = ~(a ^ b); // XNOR
      default: s_out = 1'b0;
    endcase
  end

endmodule

// Módulo de teste
module test_lu_advanced_xor_xnor;
  reg a, b;
  reg [1:0] select;
  wire s_out;

  lu_advanced_xor_xnor dut (
    .s_out(s_out),
    .a(a),
    .b(b),
    .select(select)
  );

  initial begin
 
    $display("Teste avançado LU com módulos XOR/XNOR ");
    $display(" a b select s_out");

    a = 1'b0; b = 1'b1; select = 2'b00;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 2'b01;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 2'b10;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 2'b11;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 $finish;
  end
endmodule