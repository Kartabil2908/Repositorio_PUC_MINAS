// Módulo do clock base
module clock (output clk);
    reg clk;
    
    initial begin
        clk = 1'b0; // Inicializa o clock em 0
    end
    
    always begin
        #12 clk = ~clk; // Inverte o clock a cada 12 unidades de tempo
    end
endmodule