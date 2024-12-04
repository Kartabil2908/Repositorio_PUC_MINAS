// -------------------------
// bit inequality
// -------------------------
module bitInequality (
    output neq,
    input a,
    input b
);

// descrever por portas
xor XOR1 (neq, a, b);

endmodule // bitInequality

// -------------------------
// 5-bit inequality comparator
// -------------------------
module inequalityComparator5bit (
    output neq,
    input [4:0] a,
    input [4:0] b
);

wire [4:0] neq_bits;

bitInequality BI0 (neq_bits[0], a[0], b[0]);
bitInequality BI1 (neq_bits[1], a[1], b[1]);
bitInequality BI2 (neq_bits[2], a[2], b[2]);
bitInequality BI3 (neq_bits[3], a[3], b[3]);
bitInequality BI4 (neq_bits[4], a[4], b[4]);

assign neq = neq_bits[0] | neq_bits[1] | neq_bits[2] | neq_bits[3] | neq_bits[4];

endmodule // inequalityComparator5bit

// -------------------------
// test module
// -------------------------
module test_inequalityComparator5bit;
    reg [4:0] x;
    reg [4:0] y;
    wire neq;

    inequalityComparator5bit UUT (neq, x, y);

    initial begin
    
        x = 5'b00001; y = 5'b00001;
        #1 $display("%b != %b -> %b", x, y, neq);

        x = 5'b00101; y = 5'b00011;
        #1 $display("%b != %b -> %b", x, y, neq);

        x = 5'b11111; y = 5'b11111;
        #1 $display("%b != %b -> %b", x, y, neq);

        x = 5'b10101; y = 5'b01010;
        #1 $display("%b != %b -> %b", x, y, neq);
    end
endmodule // test_inequalityComparator5bit
