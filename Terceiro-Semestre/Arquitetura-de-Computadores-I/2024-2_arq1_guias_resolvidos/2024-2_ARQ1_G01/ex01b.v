/* 
  ex01b.v 
  1449304 - 04 08 2024 
*/ 

module Guia_0101; 
// define data 
   integer   x = 13; // decimal 
   reg [7:0] b =  0;  // binary   (bits - little endian) 
 
// actions 
   initial 
    begin : main 
     $display ( "Guia_0101 - Tests" ); 
     $display ( "x = %d"  , x ); 
     $display ( "b = %8b", b ); 
     b = x; 
     $display ( "b = %8b", b ); 
    end // main 
 
endmodule // Guia_0101