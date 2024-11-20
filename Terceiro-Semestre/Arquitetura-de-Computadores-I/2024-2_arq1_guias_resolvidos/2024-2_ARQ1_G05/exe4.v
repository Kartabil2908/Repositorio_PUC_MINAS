module guia_0504
(
  output s,   // Saída do módulo
  input a,    // Primeira entrada do módulo
  input b     // Segunda entrada do módulo
);

  wire not_a, and_result; // Sinais intermediários para armazenar o valor de 'a' negado e o resultado da operação AND

  // NOT1: Realiza a negação de 'a'
  not NOT1 (not_a, a);

  // AND1: Realiza a operação AND entre 'not_a' e 'b'
  and AND1 (and_result, not_a, b);

  // NAND1: Realiza a operação NAND entre 'and_result' e 'and_result' (equivalente a uma operação NOT na variável 'and_result')
  nand NAND1 (s, and_result, and_result);

endmodule


module test_guia_0504;
  reg x, y;    
  wire s;      

  
  guia_0504 module_under_test (
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
