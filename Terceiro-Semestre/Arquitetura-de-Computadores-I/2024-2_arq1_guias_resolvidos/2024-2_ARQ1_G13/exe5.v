module tff (
    output reg q,
    output reg qnot,
    input t,
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
        end else if (t) begin
            q <= ~q;
            qnot <= ~qnot;
        end
    end
endmodule

module contador_modulo7 (
    output [2:0] q,
    input clk,
    input preset,
    input clear
);
    wire [2:0] qnot;
    wire [2:0] t;

    assign t[0] = 1'b1;
    assign t[1] = q[0];
    assign t[2] = q[0] & q[1];

    tff ff0(q[0], qnot[0], t[0], clk, preset, clear);
    tff ff1(q[1], qnot[1], t[1], clk, preset, clear);
    tff ff2(q[2], qnot[2], t[2], clk, preset, clear);

    // Reinicia o contador para 0 quando chega a 7 (111 em binário)
    always @(posedge clk) begin
        if (q == 3'b111) begin
            q <= 3'b000;
        end
    end
endmodule
