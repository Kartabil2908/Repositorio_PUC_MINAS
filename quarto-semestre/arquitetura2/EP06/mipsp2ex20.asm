.data
x_addr: .word 2
y_addr: .word 0

.text
.globl main
main:
        # Carrega endereços manualmente
        lui $s0, 0x1001       # $s0 = endereço base de x
        ori $s0, $s0, 0x0000

        lui $s1, 0x1001       # $s1 = endereço base de y
        ori $s1, $s1, 0x0004

        lw $t0, 0($s0)        # $t0 = x
        andi $t1, $t0, 1      # Verifica paridade (x % 2)
        bne $t1, $zero, impar

# --- x par: y = x^4 + x^3 - 2x^2 ---
        mult $t0, $t0         # x^2
        mflo $t2              # $t2 = x^2

        mult $t2, $t0         # x^3
        mflo $t3              # $t3 = x^3

        mult $t3, $t0         # x^4
        mflo $t4              # $t4 = x^4

        sll $t5, $t2, 1       # $t5 = 2 * x^2
        add $t6, $t4, $t3     # x^4 + x^3
        sub $t6, $t6, $t5     # - 2x^2

        sw $t6, 0($s1)
        j end

impar:
# --- x ímpar: y = x^5 - x^3 + 1 ---
        mult $t0, $t0         # x^2
        mflo $t2

        mult $t2, $t0         # x^3
        mflo $t3              # $t3 = x^3

        mult $t3, $t0         # x^4
        mflo $t4

        mult $t4, $t0         # x^5
        mflo $t5              # $t5 = x^5

        sub $t6, $t5, $t3     # x^5 - x^3
        addi $t6, $t6, 1      # + 1

        sw $t6, 0($s1)

end:
        nop
