module shift_register_left_6bit(
    output reg [5:0] q,
    input wire clk,
    input wire ld,
    input wire data_in
);
    always @(posedge clk) begin
        if (ld) begin
            q <= {data_in, q[5:1]}; // Desloca para a esquerda, insere data_in no bit 0
        end else begin
            q <= {q[4:0], 1'b0}; // Desloca para a esquerda, insere 0 no bit 0
        end
    end
endmodule
