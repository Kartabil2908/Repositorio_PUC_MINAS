// --------------
// --- Alternating Sequence FSM
// --------------

/*
                         Alternating FSM Diagram
                      __________________________
                    /                          \
              0    v     1           0         1 | // found
   [start] ---> [id0] ---> [id01] ---> [id010]  ---> [id101]
     ^  \1      0 |       1\        0 |       1 |
      \_/        /         \__/          |        |
       \________/                        |        |
        \                                |        |
         \______________________ _________/        |
          \                                       |
           \_____________________ _________________/
*/


`define found      1
`define notfound 0

// FSM by Alternating Sequence
module Guia_1105 ( y, x, clk, reset );
 output y;
 input   x;
 input   clk;
 input   reset;

 reg      y;

 parameter       
   start     = 3'b000,
   id0       = 3'b001,
   id01      = 3'b010,
   id010     = 3'b011,
   id101     = 3'b100;

   reg [2:0] E1;  
   reg [2:0] E2;  

 // next state logic
   always @( x or E1 )
    begin
     case( E1 )
      start:
        if ( x )
         E2 = id0;
        else
         E2 = start;
      id0:
        if ( x )
         E2 = start;
        else
         E2 = id01;
      id01:
        if ( x )
         E2 = id010;
        else
         E2 = start;
      id010:
        if ( x )
         E2 = id101;
        else
         E2 = start;
      id101:
        if ( x )
         E2 = id0;
        else
         E2 = start;
     default: 
         E2 = 3'bxxx;
     endcase
    end


   always @( posedge clk or negedge reset )
    begin
     if ( reset )
      E1 = E2 ;    
     else
      E1 = 0;     
    end


   always @( E1 )
    begin
     y = (E1 == id010 || E1 == id101) ? `found : `notfound;
    end 

endmodule // Guia_1105
