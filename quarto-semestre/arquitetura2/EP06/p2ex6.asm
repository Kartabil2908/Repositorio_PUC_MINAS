.text
main:
	# carregar x = 0x7FFFFFFF (maior int 32-bit)
        lui $t0, 0x7FFF        # $t0 = 0x7FFF0000
        ori $t0, $t0, 0xFFFF   # $t0 = 0x7FFFFFFF

        # y = 300000 (0x000493E0)
        lui $t1, 0x0004        # $t1 = 0x00040000
        ori $t1, $t1, 0x93E0   # $t1 = 0x000493E0 (300000 decimal)

        sll $t2, $t1, 2        # $t2 = y * 4

        sub $t3, $t0, $t2      # $t3 = x - 4*y

