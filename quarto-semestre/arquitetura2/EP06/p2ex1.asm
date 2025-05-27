# a -> $s0; b -> $s1; c -> $s2, d -> $s3; x -> $s4; y -> $s5

.text
.globl main
main:
	ori $s0, $zero, 0x0002 # a = 2
	ori $s1, $zero, 0x0003 # b = 3
	ori $s2, $zero, 0x0004 # c = 4
	ori $s3, $zero, 0x0005 # d = 5
	add $t0, $s2, $s3 # t0 = c + d
	add $t1, $s0, $s1 # t1 = a + b
	sub $s4, $t1, $t0 # x = (a+b)-(c+d)
	add $t0, $s1, $s4 # t0 = b + x
	sub $s5, $s0, $t0 # y = a - t0
	sub $s1, $s4, $s5 # b = x - y
	