module jkff (
    output reg q,
    output reg qnot,
    input j,
    input k,
    input clk,
    input preset,
    input clear
);
    always @(posedge clk or posedge preset or posedge clear) begin
        if (clear) begin
            q <= 0;
            qnot <= 1;
        end else if (preset) begin
            q <= 1;
            qnot <= 0;
        end else if (j & ~k) begin
            q <= 1;
            qnot <= 0;
        end else if (~j & k) begin
            q <= 0;
            qnot <= 1;
        end else if (j & k) begin
            q <= ~q;
            qnot <= ~qnot;
        end
    end
endmodule

module contador_decrescente (
    output [4:0] q,
    input clk,
    input preset,
    input clear
);
    wire [4:0] qnot;
    wire [4:0] clk_div;

    assign clk_div[0] = clk;
    assign clk_div[1] = q[0];
    assign clk_div[2] = q[1];
    assign clk_div[3] = q[2];
    assign clk_div[4] = q[3];

    jkff ff0(q[0], qnot[0], 1'b1, 1'b1, clk_div[0], preset, clear);
    jkff ff1(q[1], qnot[1], 1'b1, 1'b1, clk_div[1], preset, clear);
    jkff ff2(q[2], qnot[2], 1'b1, 1'b1, clk_div[2], preset, clear);
    jkff ff3(q[3], qnot[3], 1'b1, 1'b1, clk_div[3], preset, clear);
    jkff ff4(q[4], qnot[4], 1'b1, 1'b1, clk_div[4], preset, clear);
endmodule
