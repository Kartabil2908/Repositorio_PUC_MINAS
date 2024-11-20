
module ram_1x4 (
    input wire clock,        // Clock
    input wire clear,        // Limpar entrada
    input wire rw,         // Chave para controlar escrita e leitura (1 for escrita, 0 for leitura)
    input wire endereco,       // Endereço da entrada (1 bit por endereço)
    input wire [3:0] data_entrada,  // 4 bits para entrada
    output wire [3:0] data_saida // 4 bits para saida
);

    wire [3:0] q;         //Saída do flip flop JK
    wire [3:0] qnot;      // saídas complementares
    wire escrita_sinal;     // sinal de ligar a escrita
    
    
    assign escrita_sinal = rw & endereco;
    
    // 4 flip flops JK para guardar 4 bits
    jkff ff0 (
        .q(q[0]), 
        .qnot(qnot[0]),
        .j(data_entrada[0] & escrita_sinal),
        .k(~data_entrada[0] & escrita_sinal),
        .clock(clock),
        .preset(1'b0),
        .clear(clear)
    );
    
    jkff ff1 (
        .q(q[1]), 
        .qnot(qnot[1]),
        .j(data_entrada[1] & escrita_sinal),
        .k(~data_entrada[1] & escrita_sinal),
        .clock(clock),
        .preset(1'b0),
        .clear(clear)
    );
    
    jkff ff2 (
        .q(q[2]), 
        .qnot(qnot[2]),
        .j(data_entrada[2] & escrita_sinal),
        .k(~data_entrada[2] & escrita_sinal),
        .clock(clock),
        .preset(1'b0),
        .clear(clear)
    );
    
    jkff ff3 (
        .q(q[3]), 
        .qnot(qnot[3]),
        .j(data_entrada[3] & escrita_sinal),
        .k(~data_entrada[3] & escrita_sinal),
        .clock(clock),
        .preset(1'b0),
        .clear(clear)
    );

    // Saída do multiplexador
    assign data_saida = endereco ? q : 4'b0000;

endmodule