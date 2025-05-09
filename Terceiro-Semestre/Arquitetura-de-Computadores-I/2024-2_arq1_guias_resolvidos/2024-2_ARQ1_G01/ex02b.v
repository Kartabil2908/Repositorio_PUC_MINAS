/* 
  ex02b.v
  1449304 - 04 08 2024 
*/ 
module Guia_0102; 
// define data 
   integer   x = 0;                  // decimal 
   reg [7:0] b = 8'b0001101; // binary (bits - little endian) 
 
// actions 
   initial 
    begin : main 
     $display ( "Guia_0102 - Tests" ); 
     $display ( "x = %d"  , x ); 
     $display ( "b = %8b", b ); 
     x = b; 
     $display ( "b = %d", x ); 
    end // main