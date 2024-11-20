module lu_advanced (
    output reg s_out,
    input a,
    input b,
    input select_op,
    input select_group
);

  always @(*) begin
    if (select_group == 1'b0) 
    begin
      if (select_op == 1'b0) 
      begin
        s_out = ~(a & b); // NAND
      end 
      else 
      begin
        s_out = a & b; // AND
      end
    end 
    else begin

      if (select_op == 1'b0) 
      begin
        s_out = ~(a | b); // NOR
      end else 
      begin
        s_out = a | b; // OR
      end
    end
  end

endmodule

// Módulo de teste
module test_lu_advanced;
  reg a, b, select_op, select_group;
  wire s_out;

  lu_advanced dut (
    .s_out(s_out),
    .a(a),
    .b(b),
    .select_op(select_op),
    .select_group(select_group)
  );

  initial begin
    $display("Teste avançado módulo LU");
    $display(" a b select_op select_group s_out");

    a = 1'b0; b = 1'b1; select_op = 1'b0; select_group = 1'b0;
    #1 $monitor("%b %b %b %b %b", a, b, select_op, select_group, s_out);

    #1 select_op = 1'b1;
    #1 $monitor("%b %b %b %b %b", a, b, select_op, select_group, s_out);

    #1 select_group = 1'b1;
    #1 $monitor("%b %b %b %b %b", a, b, select_op, select_group, s_out);

    #1 select_op = 1'b0;
    #1 $monitor("%b %b %b %b %b", a, b, select_op, select_group, s_out);

    #1 $finish;
  end
endmodule