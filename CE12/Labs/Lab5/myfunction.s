.data
myStr: .asciiz "Hello, world! %d\n"
val:   .word 0x00000;

.ent getDelay
.text
.global getDelay
getDelay:
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

la $a0, myStr
lw $a1, val
jal printf
NOP

lw $a1, val
add $a1, $a1, 1
sw $a1, val


la $a0, myStr
lw $a1, val
jal printf
NOP

lw $a1, val
add $a1, $a1, 1
sw $a1, val

la $a0, myStr
lw $a1, val
jal printf
NOP

and $v0, $v0, 0
addi $v0, $v0, 0xF
sll $v0, $v0, 0x13

lw   $s0, 0($sp)   # Copy from stack to $r2
lw   $s1, 4($sp)   # Copy from stack to $r3
lw   $s2, 8($sp)   # Copy from stack to $r4
lw   $s3, 12($sp)   # Copy from stack to $r2
lw   $s4, 16($sp)   # Copy from stack to $r3
lw   $s5, 20($sp)   # Copy from stack to $r4
lw   $s6, 24($sp)   # Copy from stack to $r2
lw   $s7, 28($sp)   # Copy from stack to $r3
lw   $ra, 32($sp)   # Copy from stack to $r4
addi $sp, $sp, 36  # Increment stack pointer by 12

jr $ra

.end getDelay




