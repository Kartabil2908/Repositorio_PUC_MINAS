module guia_0507 
(
  output s,   // Saída do módulo
  input a,    // Primeira entrada do módulo
  input b     // Segunda entrada do módulo
);

  wire not_a, not_b, xor_result;  // Fios intermediários para armazenar os resultados

  // NOT1: Realiza a operação NOT sobre a entrada 'a'
  not NOT1 (not_a, a);
  
  // NOT2: Realiza a operação NOT sobre a entrada 'b'
  not NOT2 (not_b, b);
  
  // XOR1: Realiza a operação XOR entre 'not_a' e 'not_b'
  xor XOR1 (xor_result, not_a, not_b);
  
  // NOR1: Realiza a operação NOR entre 'xor_result' e 'xor_result'
  // Isso é equivalente a uma operação NOT no resultado da XOR
  nor NOR1 (s, xor_result, xor_result);

endmodule

module test_guia_0507;
  reg x, y;     
  wire s;      


  guia_0507 module_under_test 
  (
    .s(s),  
    .a(x), 
    .b(y)   
  );

  initial begin

    $display(" x y s");
    $monitor("%4b %4b %4b", x, y, s);

    // Testa todas as combinações possíveis de x e y
    
    x = 1'b0; y = 1'b0;  // Primeiro caso: x = 0, y = 0
    #1 x = 1'b0; y = 1'b1;  // Segundo caso: x = 0, y = 1
    #1 x = 1'b1; y = 1'b0;  // Terceiro caso: x = 1, y = 0
    #1 x = 1'b1; y = 1'b1;  // Quarto caso: x = 1, y = 1
  end
endmodule
