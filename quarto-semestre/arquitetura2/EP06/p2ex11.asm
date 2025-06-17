# y = x – z + 300000 
# end base -> $t0
# x -> $s0
# y -> $s1
# z -> $s2

.text
.globl main
main:

	lui $t0, 0x1001      # $t0 = 0x10010000 (endereço base para .data)

    	#carregando os valores
    	lw $s0, 0($t0)       # x = Memory[0x10010000 + 0]  (x = 100000)
    	lw $s2, 4($t0)       # z = Memory[0x10010000 + 4]  (z = 200000)

    	# Calculando y = x - z + 300000
    	sub $t1, $s0, $s2    # $t1 = x - z  (100000 - 200000 = -100000)

    	# Carregar a constante 300000 em um registrador
    	# 300000 em hexadecimal é 0x000493E0
    	lui $t2, 0x0004      # $t2 = 0x00040000
    	ori $t2, $t2, 0x93E0 # $t2 = 0x000493E0 (300000)

    	add $s1, $t1, $t2    # $s1 = (x - z) + 300000 (-100000 + 300000 = 200000)

    	# Armazenando o resultado y na memória
    	sw $s1, 8($t0)       # Memory[0x10010000 + 8] = y
	
	
	

.data 
x: .word 100000 
z: .word 200000
y: .word 0 # esse valor deverá ser sobrescrito após a execução do programa.
