module comparador_igualdade (
    output reg s_out,
    input [2:0] a,
    input [2:0] b,
    input select
);

  wire [2:0] xnor_resultado;

  genvar i;
  generate
    for (i = 0; i < 3; i = i + 1) 
    begin
      assign xnor_resultado[i] = a[i] ~^ b[i];
    end
  endgenerate

  always @(*) begin
    if (select == 1'b0) 
    begin
      s_out = &xnor_resultado; // Igualdade
    end 
    else begin
      s_out = ~(&xnor_resultado); // Diferença
    end
  end

endmodule

// Módulo de teste
module test_comparador_igualdade;
  reg [2:0] a, b;
  reg select;
  wire s_out;

  comparador_igualdade dut (
    .s_out(s_out),
    .a(a),
    .b(b),
    .select(select)
  );

  initial begin
    $display("Teste do módulo do comparador de igualdade");
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