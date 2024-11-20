// RAM 4x16 utilizando módulos RAM 4x8
module ram_4x16 (
    input wire clk,               // Sinal de clock
    input wire clr,               // Sinal de reset
    input wire rw,                // Sinal de controle de leitura/escrita
    input wire [2:0] addr,        // Endereço de 3 bits (4 locações)
    input wire [15:0] data_in,    // Dados de entrada de 16 bits
    output wire [15:0] data_out    // Dados de saída de 16 bits
);

    // Instanciação dos módulos RAM 4x8 para os bytes inferior e superior
    ram_4x8 lower_byte (
        .clk(clk),
        .clr(clr),
        .rw(rw),
        .addr(addr),
        .data_in(data_in[7:0]),      // Dados de entrada para o byte inferior
        .data_out(data_out[7:0])     // Dados de saída do byte inferior
    );
    
    ram_4x8 upper_byte (
        .clk(clk),
        .clr(clr),
        .rw(rw),
        .addr(addr),
        .data_in(data_in[15:8]),     // Dados de entrada para o byte superior
        .data_out(data_out[15:8])    // Dados de saída do byte superior
    );

endmodule
