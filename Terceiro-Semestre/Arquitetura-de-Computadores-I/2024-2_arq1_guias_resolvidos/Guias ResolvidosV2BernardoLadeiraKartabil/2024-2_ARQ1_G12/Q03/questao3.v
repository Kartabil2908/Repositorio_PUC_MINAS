module ram_2x8 (
    input wire clock,              // Sinal de clock
    input wire clear,              // Sinal de reset
    input wire rw,                 // Sinal de controle de leitura/escrita
    input wire [1:0] endereco,     // Endereço de 2 bits (2 locações)
    input wire [7:0] data_in,      // Dados de entrada de 8 bits
    output wire [7:0] data_out      // Dados de saída de 8 bits
);

    wire [7:0] data_out_0;         // Saída do primeiro módulo de RAM
    wire [7:0] data_out_1;         // Saída do segundo módulo de RAM
    wire endereco1, endereco2;     // Sinais de seleção de endereço

    // Lógica para selecionar os endereços
    assign endereco1 = (endereco == 2'b00);
    assign endereco2 = (endereco == 2'b01);

    // Instanciação dos módulos 1x8 RAM
    ram_1x8 mem0 (
        .clock(clock),
        .clear(clear),
        .rw(rw & endereco1),          // Controle de leitura/escrita para o módulo 0
        .endereco(1'b1),              // Endereço fixo para o módulo 0
        .data_in(data_in),
        .data_out(data_out_0)
    );
    
    ram_1x8 mem1 (
        .clock(clock),
        .clear(clear),
        .rw(rw & endereco2),          // Controle de leitura/escrita para o módulo 1
        .endereco(1'b1),              // Endereço fixo para o módulo 1
        .data_in(data_in),
        .data_out(data_out_1)
    );

    // Multiplexador para selecionar a saída
    assign data_out = endereco1 ? data_out_0 :
                      endereco2 ? data_out_1 :
                      8'b0; // Valor padrão se nenhum endereço for selecionado

endmodule
