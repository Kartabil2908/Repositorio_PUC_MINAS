module ring_shift_register_right_6bit(
    output reg [5:0] q,
    input wire clk,
    input wire ld,
    input wire data_in
);
    always @(posedge clk) begin
        if (ld) begin
            q[0] <= data_in;
            q[5:1] <= q[4:0];
        end else begin
            q <= {q[0], q[5:1]}; // Desloca para a direita circularmente
        end
    end
endmodule
