// Módulo de meia-diferença (half subtractor)
module MeiaDiferenca(
    output d,
    output v,
    input a,
    input b
);
    xor (d, a, b);
    and (v, a, b);
endmodule

// Módulo de subtração completa (full subtractor)
module fullSubtractor(
    output s0,
    output s1,
    input a,
    input b,
    input borrowIn
);
    wire w1, w2, w3;
    
    MeiaDiferenca HS1 (.d(w1), .v(w2), .a(a), .b(b));
    MeiaDiferenca HS2 (.d(s0), .v(w3), .a(w1), .b(borrowIn));
    or (s1, w2, w3);
endmodule

// Módulo de unidade aritmética (AU)
module arithmeticUnit(
    output [4:0] diff,
    output borrowOut,
    input [4:0] a,
    input [4:0] b
);
    wire [3:0] borrowWires;
    
    fullSubtractor FS0 (.s0(diff[0]), .s1(borrowWires[0]), .a(a[0]), .b(b[0]), .borrowIn(1'b0));
    fullSubtractor FS1 (.s0(diff[1]), .s1(borrowWires[1]), .a(a[1]), .b(b[1]), .borrowIn(borrowWires[0]));
    fullSubtractor FS2 (.s0(diff[2]), .s1(borrowWires[2]), .a(a[2]), .b(b[2]), .borrowIn(borrowWires[1]));
    fullSubtractor FS3 (.s0(diff[3]), .s1(borrowWires[3]), .a(a[3]), .b(b[3]), .borrowIn(borrowWires[2]));
    fullSubtractor FS4 (.s0(diff[4]), .s1(borrowOut), .a(a[4]), .b(b[4]), .borrowIn(borrowWires[3]));
endmodule

// Módulo de teste
module testArithmeticUnit;
    reg [4:0] a, b;
    wire [4:0] diff;
    wire borrowOut;
    
    arithmeticUnit AU (.diff(diff), .borrowOut(borrowOut), .a(a), .b(b));
    
    initial begin
        $display("Testando Unidade Aritmética com Subtrator Completo");
        
        a = 5'b10101; b = 5'b01010;
        #10 $display("a = %b, b = %b, diff = %b, borrowOut = %b", a, b, diff, borrowOut);
        
        a = 5'b11111; b = 5'b00001;
        #10 $display("a = %b, b = %b, diff = %b, borrowOut = %b", a, b, diff, borrowOut);
        
        $finish;
    end
endmodule