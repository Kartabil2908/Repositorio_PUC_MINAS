module parallel_to_serial_6bit(
    output reg serial_out,
    input wire clk,
    input wire ld,
    input wire [5:0] parallel_in
);
    reg [5:0] shift_reg;
    integer i;

    always @(posedge clk) begin
        if (ld) begin
            shift_reg <= parallel_in;
            i <= 5;
        end else if (i >= 0) begin
            serial_out <= shift_reg[i];
            i <= i - 1;
        end
    end
endmodule
