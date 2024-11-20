// RAM 8x8 utilizando módulos RAM 4x8
module ram_8x8 (
    input wire clk,               // Sinal de clock
    input wire clr,               // Sinal de reset
    input wire rw,                // Sinal de controle de leitura/escrita
    input wire [3:0] addr,        // Endereço de 4 bits (8 locações)
    input wire [7:0] data_in,     // Dados de entrada de 8 bits
    output wire [7:0] data_out     // Dados de saída de 8 bits
);

    wire [7:0] data_out_low;      // Saída do bloco inferior
    wire [7:0] data_out_high;     // Saída do bloco superior
    wire select_low, select_high; // Sinais de seleção para os blocos de RAM

    // Lógica de seleção de bloco
    assign select_low = ~addr[3]; // Seleciona o bloco inferior
    assign select_high = addr[3];  // Seleciona o bloco superior

    // Instanciação dos módulos RAM 4x8
    ram_4x8 lower_block (
        .clk(clk),
        .clr(clr),
        .rw(rw & select_low),        // Controle de leitura/escrita para o bloco inferior
        .addr(addr[2:0]),            // Usa os 3 bits inferiores do endereço
        .data_in(data_in),
        .data_out(data_out_low)
    );
    
    ram_4x8 upper_block (
        .clk(clk),
        .clr(clr),
        .rw(rw & select_high),       // Controle de leitura/escrita para o bloco superior
        .addr(addr[2:0]),            // Usa os 3 bits inferiores do endereço
        .data_in(data_in),
        .data_out(data_out_high)
    );

    // Multiplexador para selecionar a saída
    assign data_out = select_low ? data_out_low :
                      select_high ? data_out_high :
                      8'b0; // Valor padrão se nenhum bloco for selecionado

endmodule
