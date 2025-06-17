.text 
.globl main
main:
	#programa 4 
	ori $s0, $zero, 3
	ori $s1, $zero, 4
	sll $t0, $s0, 4 #t0=16x
	sub $t0, $t0, $s0 #t0=16x-x
	sll $t1, $s1, 6 #t1=64y
	add $t1, $t1, $s1 #t1=65y
	add $t1, $t1, $s1 #t1=66y
	add $t1, $t1, $s1 #t1=67y
	add $t0, $t0, $t1 #t0=15x+67y
	sll $s2, $t0, 2
