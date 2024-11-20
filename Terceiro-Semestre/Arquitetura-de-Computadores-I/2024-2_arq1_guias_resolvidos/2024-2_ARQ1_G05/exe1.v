module guia_0501
(
  output s,   // Saída do módulo
  input a,    // Primeira entrada do módulo
  input b     // Segunda entrada do módulo
);

  wire not_a; // Sinal intermediário para armazenar o valor de 'a' negado

  // NOR1: Realiza a negação de 'a' usando a porta NOR com entradas iguais
  nor NOR1 (not_a, a, a);
  
  // NOR2: Calcula a saída 's' aplicando a operação NOR entre 'not_a' e 'b'
  nor NOR2 (s, not_a, b);

endmodule

module test_guia_0501;
  reg x, y;     // Registros para simular entradas x e y
  wire s;       // Fio para capturar a saída do módulo testado

  guia_0501 module_under_test (
    .s(s),  // Conecta a saída 's' do módulo ao fio 's' no testbench
    .a(x),  // Conecta a entrada 'a' do módulo à variável 'x'
    .b(y)   // Conecta a entrada 'b' do módulo à variável 'y'
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
