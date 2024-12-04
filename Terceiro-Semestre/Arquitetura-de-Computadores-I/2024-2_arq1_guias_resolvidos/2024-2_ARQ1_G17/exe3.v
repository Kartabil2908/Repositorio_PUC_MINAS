module fsm_jk_toggle (
    input wire clk,
    input wire reset,
    input wire a, b, c,
    output reg [2:0] state
);
    always @(posedge clk or posedge reset) begin
        if (reset)
            state <= 3'b000;
        else begin
            case (state)
                3'b000: if (a & b & c) state <= 3'b001; else state <= 3'b000;
                3'b001: if (a & b & c) state <= 3'b011; else state <= 3'b010;
                3'b010: if (a & b & c) state <= 3'b011; else state <= 3'b010;
                3'b011: if (a & b & c) state <= 3'b111; else state <= 3'b110;
                3'b100: if (a & b & c) state <= 3'b101; else state <= 3'b100;
                3'b101: if (a & b & c) state <= 3'b000; else state <= 3'b001;
                3'b110: if (a & b & c) state <= 3'b111; else state <= 3'b110;
                3'b111: if (a & b & c) state <= 3'b000; else state <= 3'b001;
                default: state <= 3'b000;
            endcase
        end
    end
endmodule
