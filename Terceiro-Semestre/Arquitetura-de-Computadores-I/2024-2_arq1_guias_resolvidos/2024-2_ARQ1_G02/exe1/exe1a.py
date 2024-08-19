def bin2double(string_binario):
    NumDecimal = 0.0
    potenciaDe2 = 1.0

    for bit in string_binario:
        potenciaDe2 = potenciaDe2 / 2.0
        if bit == '1':
            NumDecimal += potenciaDe2

    return NumDecimal

b = "1011"  # Exemplo de string binária
resultado = bin2double(b)
print(f"O número binário {b} é {resultado:.6f} em decimal")

