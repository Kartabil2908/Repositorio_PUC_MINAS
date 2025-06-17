.data
x_addr: .word -2
y_addr: .word 0

.text
.globl main
main:
        lui $s0, 0x1001
        ori $s0, $s0, 0x0000

        lui $s1, 0x1001
        ori $s1, $s1, 0x0004

        lw $t0, 0($s0)        # $t0 = x

        slt $t1, $zero, $t0   # $t1 = 1 se x > 0
        beq $t1, $zero, less_equal_zero

# --- x > 0: y = x^3 + 1 ---
        mult $t0, $t0
        mflo $t2              # x^2

        mult $t2, $t0
        mflo $t3              # x^3

        addi $t3, $t3, 1
        sw $t3, 0($s1)
        j end

less_equal_zero:
# --- x <= 0: y = x^4 - 1 ---
        mult $t0, $t0
        mflo $t2              # x^2

        mult $t2, $t0
        mflo $t3              # x^3

        mult $t3, $t0
        mflo $t4              # x^4

        addi $t4, $t4, -1
        sw $t4, 0($s1)

end:
        nop