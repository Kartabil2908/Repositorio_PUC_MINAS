# x -> $s0, y -> $s1

.data
valores: 
x: .word 12                  # Define x = 12
y: .word 520                 # Define y = 520

.text
.globl main

main:

        lui   $t2, 0x1001         # Carrega parte alta do endereço base (.data)
        ori   $t2, $t2, 0x0000    # Completa o endereço em $t2 (valores)

        # Carrega os dois números
        lw    $s0, 0($t2)         # Carrega x (12) em $s0
        lw    $s1, 4($t2)         # Carrega y (520) em $s1

        # Conta bits significativos de $s0 → $t0
        add   $t0, $zero, $zero   # Zera $t0 (contador)

conta_s0:
        beq   $s0, $zero, fim_s0  # Se $s0 == 0, fim da contagem
        srl   $s0, $s0, 1         # Desloca $s0 1 bit à direita
        addi  $t0, $t0, 1         # Incrementa contador
        j     conta_s0            # Loop

fim_s0:

        # Conta bits significativos de $s1 → $t1
        add   $t1, $zero, $zero   # Zera $t1 (contador)

conta_s1:
        beq   $s1, $zero, fim_s1  # Se $s1 == 0, fim da contagem
        srl   $s1, $s1, 1         # Desloca $s1 1 bit à direita
        addi  $t1, $t1, 1         # Incrementa contador
        j     conta_s1            # Loop

fim_s1:

        # Recarrega os números originais para multiplicar
        lw    $s0, 0($t2)         # Recarrega x em $s0
        lw    $s1, 4($t2)
