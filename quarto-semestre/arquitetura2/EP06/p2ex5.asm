.text 
.globl main
main:
	#programa 5
	#100000 = 0x186A0
	ori $t0, $zero, 0x186A 
	sll $s0, $t0, 4 #s0=100000
	#200000 = 0X30D40
	ori $t0, $zero, 0x30D4
	sll $s1, $t0, 4 #s1=200000 (4 shifts para esquerda)
	add $s2, $s0, $s1
