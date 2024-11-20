module lu_or_nor (
    output reg s_or,
    input a,
    input b,
    input select
);

  always @(*) begin
    if (select == 1'b0) begin
      s_or = a | b;
    end else begin
      s_or = ~(a | b);
    end
  end

endmodule

// Módulo de teste
module test_lu_or_nor;
  reg a, b, select;
  wire s_or;

  lu_or_nor dut (
    .s_or(s_or),
    .a(a),
    .b(b),
    .select(select)
  );

  initial begin
    $display("Teste LU módulo OR/NOR");
    $display(" a b select s_or");

    a = 1'b0; b = 1'b1; select = 1'b0;
    #1 $monitor("%b %b %b %b", a, b, select, s_or);

    #1 select = 1'b1;
    #1 $monitor("%b %b %b %b", a, b, select, s_or);

    #1 $finish;
  end
endmodule