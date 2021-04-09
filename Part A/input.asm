lw $s1, 0x4($s0)
lw $s2, 0x4($s0)
beq $s1, $s2, 0x1
lw $s3, 0x8($s0)
add $s4, $s1, $s2