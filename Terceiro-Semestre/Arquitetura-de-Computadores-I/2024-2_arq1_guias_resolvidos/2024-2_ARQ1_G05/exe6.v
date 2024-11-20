module guia_0506 
(
  output s,   // Saída do módulo
  input a,    // Primeira entrada do módulo
  input b     // Segunda entrada do módulo
);

  wire xor_result; // Sinal intermediário para armazenar o resultado da operação XOR

  // XOR1: Realiza a operação XOR entre as entradas 'a' e 'b'
  xor XOR1 (xor_result, a, b);

  // NAND1: Realiza a operação NAND entre 'xor_result' e 'xor_result' (equivalente a uma operação NOT na variável 'xor_result')
  nand NAND1 (s, xor_result, xor_result);

endmodule


module test_guia_0506;
  reg x, y;     
  wire s;     

  guia_0506 module_under_test (
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
