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
// equality/inequality comparator (6-bit)
// -------------------------
module comparator6bit (
    output result,
    input [5:0] a,
    input [5:0] b,
    input select
);

wire equality, inequality;

equalityComparator6bit EQ6 (equality, a, b);
inequalityComparator6bit NEQ6 (inequality, a, b);

assign result = (select == 1'b0) ? equality : inequality;

endmodule // comparator6bit

// -------------------------
// test module
// -------------------------
module test_comparator6bit;
    reg [5:0] x;
    reg [5:0] y;
    reg select;
    wire result;

    comparator6bit UUT (result, x, y, select);

    initial begin
        $display("Guia_0807 - Bernardo - 123456");
        $display("Test 6-bit Equality/Inequality Comparator");
        
        x = 6'b000001; y = 6'b000001; select = 0;
        #1 $display("%b == %b -> %b (select = %b)", x, y, result, select);

        x = 6'b001010; y = 6'b000111; select = 0;
        #1 $display("%b == %b -> %b (select = %b)", x, y, result, select);

        x = 6'b111111; y = 6'b000001; select = 1;
        #1 $display("%b != %b -> %b (select = %b)", x, y, result, select);

        x = 6'b101010; y = 6'b010101; select = 1;
        #1 $display("%b != %b -> %b (select = %b)", x, y, result, select);
    end
endmodule // test_comparator6bit
