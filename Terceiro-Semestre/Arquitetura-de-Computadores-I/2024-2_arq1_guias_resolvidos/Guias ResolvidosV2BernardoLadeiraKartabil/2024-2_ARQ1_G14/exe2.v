module shift_register_left_6bit_initial_load(
    output reg [5:0] q,
    input wire clk,
    input wire ld,
    input wire [5:0] data_in
);
    always @(posedge clk) begin
        if (ld) begin
            q <= data_in; // Carrega data_in em todos os estágios
        end else begin
            q <= {q[4:0], 1'b0}; // Desloca para a esquerda, insere 0 no bit 0
        end
    end
endmodule
