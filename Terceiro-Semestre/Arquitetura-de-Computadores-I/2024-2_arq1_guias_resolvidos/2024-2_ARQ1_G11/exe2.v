// --------------  
// --- Moore FSM  
// --------------  

/* 
                               Moore FSM Diagram  
                             _________________ 
                            /                 \ 
           1         1      v     0          1   1| // found  
   [start] ---> [id1] ---> [id11] --->> [id110]  ---> [id1101]  
     ^  \0      0 |       1^  \        0 |       0| 
      \_/        /         \__/          |        | 
       \________/                        |        | 
        \                                |        | 
         \________________________ ______/        | 
          \                                       | 
           \________________________ _____________/ 
*/ 

// Constantes    
`define found      1  
`define notfound   0  

// FSM by Moore  
module moore_1101 (y, x, clk, reset);  
  output y;  
  input x;  
  input clk;  
  input reset;  
  
  reg y;  
  
 // Identificadores de estado    
  parameter start  = 3'b000,  
            id1    = 3'b001,  
            id11   = 3'b011,  
            id110  = 3'b010,  
            id1101 = 3'b110;  // sinal encontrado  
  
  reg [2:0] E1;  // variáveis do estado atual 
  reg [2:0] E2;  // saída do próximo estado lógico
  
  // próximo estado lógico
  always @(x or E1) begin  
    case (E1)  
      start:  
        if (x)  
          E2 = id1;  
        else 
          E2 = start;  
      id1: 
        if (x)  
          E2 = id11;  
        else 
          E2 = start;  
      id11:  
        if (x) 
          E2 = id11;  
        else 
          E2 = id110;  
      id110:  
        if (x)  
          E2 = id1101;  
        else 
          E2 = start; 
      id1101:  
        if (x)  
          E2 = id11;  
        else 
          E2 = start;  
      default:   // estado indefinido 
        E2 = 3'bxxx;  
    endcase  
  end
  
  // variáveis do estado 
  always @(posedge clk or negedge reset) begin  
    if (reset)  
      E1 = E2;    // atualiza o estado atual 
    else 
      E1 = 0;     // reset 
  end 
  
  // output logic  
  always @(E1) begin  
    y = E1[2];   // primeiro bit do valor do estado (indicador MOORE)
  end 
  
endmodule // moore_1101  
