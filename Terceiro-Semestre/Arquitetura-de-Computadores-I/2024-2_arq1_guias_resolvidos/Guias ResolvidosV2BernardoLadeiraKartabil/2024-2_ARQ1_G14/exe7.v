module twisted_ring_shift_register_right_5bit(
    output reg [4:0] q,
    input wire clk,
    input wire ld,
    input wire [4:0] data_in
);
    always @(posedge clk) begin
        if (ld) begin
            q <= data_in; // Carrega data_in em todos os estágios
        end else begin
            q <= {q[0], q[4:1]}; // Desloca para a direita circularmente com twist
        end
    end
endmodule
