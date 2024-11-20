module guia_0502 
(
  output s,   // Saída do módulo
  input a,    // Primeira entrada do módulo
  input b     // Segunda entrada do módulo
);

  wire not_b; // Sinal intermediário para armazenar o valor de 'b' negado

  // NOT1: Realiza a negação de 'b'
  not NOT1 (not_b, b);

  // NAND1: Realiza a operação NAND entre 'a' e 'not_b' (negado de 'b')
  nand NAND1 (s, a, not_b);

endmodule

module test_guia_0502;
  reg x, y;     
  wire s; 

  guia_0502 module_under_test (
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
