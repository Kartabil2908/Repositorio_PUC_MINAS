module async_counter (
    input wire clk,
    input wire reset,
    output reg [4:0] q
);
    always @(posedge clk or posedge reset) begin
        if (reset)
            q <= 5'b00000;
        else
            q <= q + 1;
    end
endmodule
