module lu_abrangente (
    output reg s_out,
    input a,
    input b,
    input [2:0] select
);

  always @(*) begin
    case (select)
      3'b000: s_out = ~a; // NOT
      3'b001: s_out = a & b; // AND
      3'b010: s_out = ~(a & b); // NAND
      3'b011: s_out = a | b; // OR
      3'b100: s_out = ~(a | b); // NOR
      3'b101: s_out = a ^ b; // XOR
      3'b110: s_out = ~(a ^ b); // XNOR
      default: s_out = 1'bx; // Seleção  inválida

    endcase
  end

endmodule

// Módulo de teste
module test_lu_abrangente;
  reg a, b;
  reg [2:0] select;
  wire s_out;

  lu_abrangente dut (
    .s_out(s_out),
    .a(a),
    .b(b),
    .select(select)
  );

  initial begin

    $display("Teste módulo LU abrangente");
    $display(" a b select s_out");

    a = 1'b0; b = 1'b1; select = 3'b000;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b001;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b010;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b011;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b100;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b101;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b110;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 select = 3'b111;
    #1 $monitor("%b %b %b %b", a, b, select, s_out);

    #1 $finish;
  end
endmodule