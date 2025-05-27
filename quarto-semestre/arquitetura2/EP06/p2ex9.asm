# x1 -> $t0; x2 -> $t1; x3 -> $t2; x4 -> $t3; soma -> $t4

.text 
.globl main 
main:
	# colocar os valores em registradores
	lui $s0, 0x1001         # endereço base do segmento .data (0x10010000)
    	ori $s0, $s0, 0x0000

    	lw $t0, 0($s0)          # x1
    	lw $t1, 4($s0)          # x2
    	lw $t2, 8($s0)          # x3
    	lw $t3, 12($s0)         # x4

    	add $t4, $t0, $t1	# soma = x1 + x2
    	add $t4, $t4, $t2	# soma = soma + x3
    	add $t4, $t4, $t3	#soma = soma + x4

    	sw $t4, 16($s0)         # EnderecoSoma = s0 + 16

.data 
x1: .word 15 
x2: .word 25 
x3: .word 13 
x4: .word 17 
soma: .word -1
