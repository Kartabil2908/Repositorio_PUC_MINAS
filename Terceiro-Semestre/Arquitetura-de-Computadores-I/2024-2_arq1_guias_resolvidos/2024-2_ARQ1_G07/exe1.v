module lu_and_nand (
    output reg s_and,
    output reg s_nand,
    input a,
    input b,
    input select
);

  always @(*) begin
    if (select == 1'b0) begin
      s_nand = ~(a & b);
      s_and = 1'b0; // Desabilita a saída AND
    end else begin
      s_and = a & b;
      s_nand = 1'b0; // Desabilita a saída NAND
    end
  end

endmodule

// Módulo de teste
module test_lu_and_nand;
  reg a, b, select;
  wire s_and, s_nand;

  lu_and_nand dut (
    .s_and(s_and),
    .s_nand(s_nand),
    .a(a),
    .b(b),
    .select(select)
  );

  initial begin
    $display("Teste LU módulo AND/NAND ");
    $display(" a b select s_and s_nand");

    a = 1'b0; b = 1'b1; select = 1'b0;
    #1 $monitor("%b %b %b %b %b", a, b, select, s_and, s_nand);

    #1 select = 1'b1;
    #1 $monitor("%b %b %b %b %b", a, b, select, s_and, s_nand);

    #1 $finish;
  end
endmodule