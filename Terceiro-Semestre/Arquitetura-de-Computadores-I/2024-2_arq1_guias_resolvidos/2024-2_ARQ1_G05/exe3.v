module guia_0503
(
  output s,   // Saída do módulo
  input a,    // Primeira entrada do módulo
  input b     // Segunda entrada do módulo
);

  wire not_a, or_result; // Sinais intermediários para armazenar o valor de 'a' negado e o resultado da operação OR

  // NOT1: Realiza a negação de 'a'
  not NOT1 (not_a, a);

  // OR1: Realiza a operação OR entre 'not_a' e 'b'
  or OR1 (or_result, not_a, b);

  // NOR1: Realiza a operação NOR entre 'or_result' e 'or_result' (que equivale a uma operação NOT na variável 'or_result')
  nor NOR1 (s, or_result, or_result);

endmodule


module test_guia_0503;
  reg x, y;    
  wire s;       

 
  guia_0503 module_under_test (
    .s(s),  
    .a(x),  
    .b(y)   
  );

  initial begin
    $display(" x y s");
    $monitor("%4b %4b %4b", x, y, s);

    // Testa todas as combinações de valores de x e y
    
    x = 1'b0; y = 1'b0;  // Primeiro caso: x = 0, y = 0
    #1 x = 1'b0; y = 1'b1;  // Segundo caso: x = 0, y = 1
    #1 x = 1'b1; y = 1'b0;  // Terceiro caso: x = 1, y = 0
    #1 x = 1'b1; y = 1'b1;  // Quarto caso: x = 1, y = 1
  end
endmodule
