// Módulo de meia-soma (half adder)
module halfAdder(
    output s0,
    output s1,
    input a,
    input b
);
    xor (s0, a, b);
    and (s1, a, b);
endmodule

// Módulo de soma completa (full adder)
module fullAdder(
    output s0,
    output s1,
    input a,
    input b,
    input carryIn
);
    wire w1, w2, w3;
    
    halfAdder HA1 (.s0(w1), .s1(w2), .a(a), .b(b));
    halfAdder HA2 (.s0(s0), .s1(w3), .a(w1), .b(carryIn));
    or (s1, w2, w3);
endmodule

// Módulo de unidade aritmética (AU)
module arithmeticUnit(
    output [4:0] sum,
    output carryOut,
    input [4:0] a,
    input [4:0] b
);
    wire [3:0] carryWires;
    
    fullAdder FA0 (.s0(sum[0]), .s1(carryWires[0]), .a(a[0]), .b(b[0]), .carryIn(1'b0));
    fullAdder FA1 (.s0(sum[1]), .s1(carryWires[1]), .a(a[1]), .b(b[1]), .carryIn(carryWires[0]));
    fullAdder FA2 (.s0(sum[2]), .s1(carryWires[2]), .a(a[2]), .b(b[2]), .carryIn(carryWires[1]));
    fullAdder FA3 (.s0(sum[3]), .s1(carryWires[3]), .a(a[3]), .b(b[3]), .carryIn(carryWires[2]));
    fullAdder FA4 (.s0(sum[4]), .s1(carryOut), .a(a[4]), .b(b[4]), .carryIn(carryWires[3]));
endmodule

// Módulo de teste
module testArithmeticUnit;
    reg [4:0] a, b;
    wire [4:0] sum;
    wire carryOut;
    
    arithmeticUnit AU (.sum(sum), .carryOut(carryOut), .a(a), .b(b));
    
    initial begin
        $display("Testando Unidade Aritmética com Somador Completo");
        
        a = 5'b10101; b = 5'b01010;
        #10 $display("a = %b, b = %b, sum = %b, carryOut = %b", a, b, sum, carryOut);
        
        a = 5'b11111; b = 5'b00001;
        #10 $display("a = %b, b = %b, sum = %b, carryOut = %b", a, b, sum, carryOut);
        
        $finish;
    end
endmodule