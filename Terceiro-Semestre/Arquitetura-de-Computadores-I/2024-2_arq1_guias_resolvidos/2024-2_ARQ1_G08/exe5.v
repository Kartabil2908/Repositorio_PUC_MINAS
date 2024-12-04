// -------------------------
// complemento de 1
// -------------------------
module complemento1 (
    output [5:0] comp1,
    input [5:0] a
);

// descrever por portas
not NOT0 (comp1[0], a[0]);
not NOT1 (comp1[1], a[1]);
not NOT2 (comp1[2], a[2]);
not NOT3 (comp1[3], a[3]);
not NOT4 (comp1[4], a[4]);
not NOT5 (comp1[5], a[5]);

endmodule // complemento1

// -------------------------
// full adder (1-bit)
// -------------------------
module fullAdder (
    output sum, 
    output carryOut,   
    input a,  
    input b,  
    input carryIn
); 

wire ha1_sum, ha1_carry, ha2_sum, ha2_carry;

xor XOR1 (ha1_sum, a, b);
and AND1 (ha1_carry, a, b);
xor XOR2 (sum, ha1_sum, carryIn);
and AND2 (ha2_carry, ha1_sum, carryIn);
or OR1 (carryOut, ha1_carry, ha2_carry);

endmodule // fullAdder

// -------------------------
// 6-bit adder
// -------------------------
module adder6bit (
    output [5:0] sum,
    input [5:0] a,
    input [5:0] b
);

wire [5:0] carry;

fullAdder FA0 (sum[0], carry[0], a[0], b[0], 1'b0);
fullAdder FA1 (sum[1], carry[1], a[1], b[1], carry[0]);
fullAdder FA2 (sum[2], carry[2], a[2], b[2], carry[1]);
fullAdder FA3 (sum[3], carry[3], a[3], b[3], carry[2]);
fullAdder FA4 (sum[4], carry[4], a[4], b[4], carry[3]);
fullAdder FA5 (sum[5], carry[5], a[5], b[5], carry[4]);

endmodule // adder6bit

// -------------------------
// complemento de 2
// -------------------------
module complemento2 (
    output [5:0] comp2,
    input [5:0] a
);

wire [5:0] comp1;
wire [5:0] one = 6'b000001;

complemento1 C1 (comp1, a);
adder6bit A6 (comp2, comp1, one);

endmodule // complemento2

// -------------------------
// teste
// -------------------------
module test_complemento2;
    reg [5:0] x;
    wire [5:0] comp2;

    complemento2 UUT (comp2, x);

    initial begin
    
        x = 6'b000001;
        #1 $display("Complemento de 2 de %b é %b", x, comp2);

        x = 6'b000011;
        #1 $display("Complemento de 2 de %b é %b", x, comp2);

        x = 6'b111111;
        #1 $display("Complemento de 2 de %b é %b", x, comp2);

        x = 6'b101010;
        #1 $display("Complemento de 2 de %b é %b", x, comp2);
    end
endmodule // test_complemento2
