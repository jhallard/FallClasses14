.ent myfunction
.text
.global myfunction
myfunction:
addi $sp, $sp, -36  # Decrement stack pointer by 36 (9 word)
sw   $s0, 0($sp)   # Save $r2 to stack
sw   $s1, 4($sp)   # Save $r3 to stack
sw   $s2, 8($sp)   # Save $r4 to stack
sw   $s3, 12($sp)   # Save $r4 to stack
sw   $s4, 16($sp)   # Save $r4 to stack
sw   $s5, 20($sp)   # Save $r4 to stack
sw   $s6, 24($sp)   # Save $r4 to stack
sw   $s7, 28($sp)   # Save $r4 to stack
sw   $ra, 32($sp)  # save return address

addi $v0, $r0, 0x00001
sll $v0, $v0, 0x13

lw   $ra, 0($sp)
add $sp, $sp, 4
lw   $s7, 0($sp)
add $sp, $sp, 4
lw   $s6, 0($sp)
add $sp, $sp, 4
lw   $s5, 0($sp)
add $sp, $sp, 4
lw   $s4, 0($sp)
add $sp, $sp, 4
lw   $s3, 0($sp)
add $sp, $sp, 4
lw   $s2, 0($sp)
add $sp, $sp, 4
lw   $s1, 0($sp)
add $sp, $sp, 4


jr $ra

.end myfunction



