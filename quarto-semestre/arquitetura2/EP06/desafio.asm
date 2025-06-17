.data
    num1:         .word 100000         # posição 0
    num2:         .word 50000         # posição 1
    resultado_lo: .word 0         # posição 2
    resultado_hi: .word 0         # posição 3

.text
.globl main
main:

    lui   $s0, 0x1001         # $s0 = 0x10010000
    ori   $s0, $s0, 0x0000

    # Carrega num1
    lw    $t1, 0($s0)

    # Carrega num2
    lw    $t2, 4($s0)

    # Multiplicação:
    mult  $t1, $t2

    # Parte baixa (LO) -> $t3
    mflo  $t3

    # Parte alta (HI) -> $t4
    mfhi  $t4

    # Armazena parte baixa na posição $s0 + 8
    sw    $t3, 8($s0)

    # Armazena parte alta na posição $s0 + 12
    sw    $t4, 12($s0)

