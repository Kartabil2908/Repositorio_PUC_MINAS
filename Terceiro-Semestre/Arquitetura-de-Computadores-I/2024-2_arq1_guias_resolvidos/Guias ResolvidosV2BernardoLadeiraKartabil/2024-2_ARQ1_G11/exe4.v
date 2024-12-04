// --------------  
// --- FSM 1001  
// -------------- 

// definições constantes
`define found      1  
`define notfound   0  

module Guia_1101 (y, x, clk, reset);  
  output y;  
  input x;  
  input clk;  
  input reset;  
  
  reg y;  
  
// identificadores de estado 
  parameter start = 3'b000,  
            id1   = 3'b001,  
            id10  = 3'b010,  
            id100 = 3'b011,  
            id1001 = 3'b100;  // sinal encontrado
  
  reg [2:0] E1;  // variáveis ​​de estado atual 
  reg [2:0] E2;  // saída lógica do próximo estado  
  
  // próxima lógica de estado 
  always @(x or E1) begin  
    case (E1)  
      start:  
        if (x)  
          E2 = id1;  
        else 
          E2 = start;  
      id1: 
        if (x)  
          E2 = id1;  
        else 
          E2 = id10;  
      id10:  
        if (x) 
          E2 = id100;  
        else 
          E2 = start;  
      id100:  
        if (x)  
          E2 = id1001;  
        else 
          E2 = start; 
      id1001:  
        E2 = id1001;  // permanece neste estado uma vez encontrado 
      default:   // estado indefinido  
        E2 = 3'bxxx;  
    endcase  
  end   
  
  // variáveis ​​de estado  
  always @(posedge clk or negedge reset) begin  
    if (reset)  
      E1 = E2;    // atualiza o estado atual  
    else 
      E1 = 0;     // reset 
  end
  
  // lógica de saída 
  always @(E1) begin  
    y = (E1 == id1001) ? `found : `notfound;  
  end  
  
endmodule // Guia_1101  
