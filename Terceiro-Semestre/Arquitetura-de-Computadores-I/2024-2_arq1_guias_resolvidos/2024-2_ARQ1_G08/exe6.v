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
// 6-bit adder/subtractor
// -------------------------
module adderSubtractor6bit (
    output [5:0] result,
    output carryOut,
    input [5:0] a,
    input [5:0] b,
    input sub
);

wire [5:0] b_xor_sub;
wire [5:0] carry;

xor XOR0 (b_xor_sub[0], b[0], sub);
xor XOR1 (b_xor_sub[1], b[1], sub);
xor XOR2 (b_xor_sub[2], b[2], sub);
xor XOR3 (b_xor_sub[3], b[3], sub);
xor XOR4 (b_xor_sub[4], b[4], sub);
xor XOR5 (b_xor_sub[5], b[5], sub);

fullAdder FA0 (result[0], carry[0], a[0], b_xor_sub[0], sub);
fullAdder FA1 (result[1], carry[1], a[1], b_xor_sub[1], carry[0]);
fullAdder FA2 (result[2], carry[2], a[2], b_xor_sub[2], carry[1]);
fullAdder FA3 (result[3], carry[3], a[3], b_xor_sub[3], carry[2]);
fullAdder FA4 (result[4], carry[4], a[4], b_xor_sub[4], carry[3]);
fullAdder FA5 (result[5], carryOut, a[5], b_xor_sub[5], carry[4]);

endmodule // adderSubtractor6bit

// -------------------------
// equality comparator (6-bit)
// -------------------------
module equalityComparator6bit (
    output eq,
    input [5:0] a,
    input [5:0] b
);

wire [5:0] eq_bits;

xnor XNOR0 (eq_bits[0], a[0], b[0]);
xnor XNOR1 (eq_bits[1], a[1], b[1]);
xnor XNOR2 (eq_bits[2], a[2], b[2]);
xnor XNOR3 (eq_bits[3], a[3], b[3]);
xnor XNOR4 (eq_bits[4], a[4], b[4]);
xnor XNOR5 (eq_bits[5], a[5], b[5]);

assign eq = eq_bits[0] & eq_bits[1] & eq_bits[2] & eq_bits[3] & eq_bits[4] & eq_bits[5];

endmodule // equalityComparator6bit

// -------------------------
// inequality comparator (6-bit)
// -------------------------
module inequalityComparator6bit (
    output neq,
    input [5:0] a,
    input [5:0] b
);

wire [5:0] neq_bits;

xor XOR0 (neq_bits[0], a[0], b[0]);
xor XOR1 (neq_bits[1], a[1], b[1]);
xor XOR2 (neq_bits[2], a[2], b[2]);
xor XOR3 (neq_bits[3], a[3], b[3]);
xor XOR4 (neq_bits[4], a[4], b[4]);
xor XOR5 (neq_bits[5], a[5], b[5]);

assign neq = neq_bits[0] | neq_bits[1] | neq_bits[2] | neq_bits[3] | neq_bits[4] | neq_bits[5];

endmodule // inequalityComparator6bit

// -------------------------
// ALU with equality and inequality
// -------------------------
module alu6bit (
    output [5:0] result,
    output eq,
    output neq,
    input [5:0] a,
    input [5:0] b,
    input sub,
    input select
);

wire [5:0] addSubResult;
wire equality, inequality;

adderSubtractor6bit AS6 (addSubResult, , a, b, sub);
equalityComparator6bit EQ6 (equality, a, b);
inequalityComparator6bit NEQ6 (inequality, a, b);

assign result = addSubResult;
assign eq = (select == 1'b0) ? equality : 1'bz;
assign neq = (select == 1'b1) ? inequality : 1'bz;

endmodule // alu6bit

// -------------------------
// test module
// -------------------------
module test_alu6bit;
    reg [5:0] x;
    reg [5:0] y;
    reg sub;
    reg select;
    wire [5:0] result;
    wire eq;
    wire neq;

    alu6bit UUT (result, eq, neq, x, y, sub, select);

    initial begin
        
        x = 6'b000001; y = 6'b000001; sub = 0; select = 0;
        #1 $display("%b + %b = %b, eq = %b, neq = %b", x, y, result, eq, neq);

        x = 6'b001010; y = 6'b000111; sub = 0; select = 0;
        #1 $display("%b + %b = %b, eq = %b, neq = %b", x, y, result, eq, neq);

        x = 6'b111111; y = 6'b000001; sub = 1; select = 1;
        #1 $display("%b - %b = %b, eq = %b, neq = %b", x, y, result, eq, neq);

        x = 6'b101010; y = 6'b010101; sub = 1; select = 1;
        #1 $display("%b - %b = %b, eq = %b, neq = %b", x, y, result, eq, neq);
    end
endmodule // test_alu6bit
