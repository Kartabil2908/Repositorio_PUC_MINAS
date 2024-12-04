// -------------------------
// bit equality
// -------------------------
module bitEquality (
    output eq,
    input a,
    input b
);

// descrever por portas
xnor XNOR1 (eq, a, b);

endmodule // bitEquality

// -------------------------
// 5-bit equality comparator
// -------------------------
module equalityComparator5bit (
    output eq,
    input [4:0] a,
    input [4:0] b
);

wire [4:0] eq_bits;

bitEquality BE0 (eq_bits[0], a[0], b[0]);
bitEquality BE1 (eq_bits[1], a[1], b[1]);
bitEquality BE2 (eq_bits[2], a[2], b[2]);
bitEquality BE3 (eq_bits[3], a[3], b[3]);
bitEquality BE4 (eq_bits[4], a[4], b[4]);

assign eq = eq_bits[0] & eq_bits[1] & eq_bits[2] & eq_bits[3] & eq_bits[4];

endmodule // equalityComparator5bit

// -------------------------
// test module
// -------------------------
module test_equalityComparator5bit;
    reg [4:0] x;
    reg [4:0] y;
    wire eq;

    equalityComparator5bit UUT (eq, x, y);

    initial begin

        x = 5'b00001; y = 5'b00001;
        #1 $display("%b == %b -> %b", x, y, eq);

        x = 5'b00101; y = 5'b00011;
        #1 $display("%b == %b -> %b", x, y, eq);

        x = 5'b11111; y = 5'b11111;
        #1 $display("%b == %b -> %b", x, y, eq);

        x = 5'b10101; y = 5'b01010;
        #1 $display("%b == %b -> %b", x, y, eq);
    end
endmodule
