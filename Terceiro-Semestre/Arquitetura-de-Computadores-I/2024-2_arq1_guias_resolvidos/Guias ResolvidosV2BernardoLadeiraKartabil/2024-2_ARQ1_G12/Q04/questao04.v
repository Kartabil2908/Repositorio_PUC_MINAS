module ram_4x8 (
    input wire clk,               // Sinal de clock
    input wire clr,               // Sinal de reset
    input wire rw,                // Sinal de controle de leitura/escrita
    input wire [2:0] addr,        // Endereço de 3 bits (0-7)
    input wire [7:0] data_in,     // Dados de entrada de 8 bits
    output wire [7:0] data_out     // Dados de saída de 8 bits
);

    wire [7:0] data_out_low;      // Saída do bloco inferior
    wire [7:0] data_out_high;     // Saída do bloco superior
    
    wire select_low;              // Seleção para a RAM inferior
    wire select_high;             // Seleção para a RAM superior

    // Lógica de seleção de bloco
    assign select_low = ~addr[2]; // Seleciona a RAM inferior
    assign select_high = addr[2];  // Seleciona a RAM superior

    // Instanciação dos blocos de RAM 2x8
    ram_2x8 lower_block (
        .clk(clk),
        .clr(clr),
        .rw(rw & select_low),
        .addr(addr[1:0]),
        .data_in(data_in),
        .data_out(data_out_low)
    );

    ram_2x8 upper_block (
        .clk(clk),
        .clr(clr),
        .rw(rw & select_high),
        .addr(addr[1:0]),
        .data_in(data_in),
        .data_out(data_out_high)
    );

    // Multiplexador para selecionar a saída
    assign data_out = select_low ? data_out_low :
                      select_high ? data_out_high :
                      8'b0; // Valor padrão se nenhum bloco for selecionado

endmodule
