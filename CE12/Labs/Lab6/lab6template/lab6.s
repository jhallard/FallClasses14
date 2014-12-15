
#include <WProgram.h>

/* define all global symbols here */
.global T1Setup
.global T1Stop
.global T1Start
.global milliseconds

.data
milliseconds: .word 0

.section .vector_4, code
    j T1_ISR
    nop

.text
.set noreorder

/*********************************************************************
 * Start Timer 1
 ********************************************************************/
.ent T1Start
T1Start:
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

    li $t2, 16
    la $t4, IEC0
    sw $t2, 8($t4)

    la $t0, T1CON
    li $t1, 0x8000
    sw $t1, 8($t0)

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

.end T1Start

/*********************************************************************
 * Stop Timer 1
 ********************************************************************/
.ent T1Stop
T1Stop:
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

    li $t2, 16
    la $t4, IEC0
    sw $t2, 4($t4)

    la $t0, T1CON
    li $t1, 0x8000
    sw $t1, 4($t0)


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
.end T1Stop


/*********************************************************************
 * Setup Timer 1 and interrupts (called it once)
 ********************************************************************/
.ent T1Setup
T1Setup:
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

    li $t0, 0
    la $t1, T1CON
    sw $t0, 0($t1)

    li $t3, 48
    sw $t3, 8($t1)

    la $t4, TMR1
    sw $t0, 0($t4)

    li $t4, 158
    la $t5, PR1
    sw $t4, 8($t5)

    li $t0, 16
    la $t2, IPC1
    sw $t0, 8($t2)

    li $t2, 16
    la $t3, IFS0
    sw $t2, 4($t3)

    la $t4, IEC0
    sw $t2, 8($t4)

    la $t0, T1CON
    li $t1, 0x8000
    sw $t1, 8($t0)

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
    nop

.end T1Setup


/*********************************************************************
 * This is your ISR implementation. It is called from the vector table jump.
 ********************************************************************/
T1_ISR:
    addi $sp, $sp, -68  # Decrement stack pointer by 36 (9 word)
    sw   $s0, 0($sp)   # Save $r2 to stack
    sw   $s1, 4($sp)   # Save $r3 to stack
    sw   $s2, 8($sp)   # Save $r4 to stack
    sw   $s3, 12($sp)   # Save $r4 to stack
    sw   $s4, 16($sp)   # Save $r4 to stack
    sw   $s5, 20($sp)   # Save $r4 to stack
    sw   $s6, 24($sp)   # Save $r4 to stack
    sw   $s7, 28($sp)   # Save $r4 to stack
    sw   $ra, 32($sp)  # save return address
    sw   $t0, 0($sp)   # Save $r2 to stack
    sw   $t1, 4($sp)   # Save $r3 to stack
    sw   $t2, 8($sp)   # Save $r4 to stack
    sw   $t3, 12($sp)   # Save $r4 to stack
    sw   $t4, 16($sp)   # Save $r4 to stack
    sw   $t5, 20($sp)   # Save $r4 to stack
    sw   $t6, 24($sp)   # Save $r4 to stack
    sw   $t7, 28($sp)   # Save $r4 to stack


    li $t0, 16
    la $t1, IFS0
    sw $t0, 4($t1)

    li $t2, 0
    la $t3, TMR1
    sw $t2, 0($t3)

    lw $t0, milliseconds
    add $t0, $t0, 2
    sw $t0, milliseconds

    lw   $s0, 0($sp)   # Copy from stack to $r2
    lw   $s1, 4($sp)   # Copy from stack to $r3
    lw   $s2, 8($sp)   # Copy from stack to $r4
    lw   $s3, 12($sp)   # Copy from stack to $r2
    lw   $s4, 16($sp)   # Copy from stack to $r3
    lw   $s5, 20($sp)   # Copy from stack to $r4
    lw   $s6, 24($sp)   # Copy from stack to $r2
    lw   $s7, 28($sp)   # Copy from stack to $r3
    lw   $ra, 32($sp)   # Copy from stack to $r4
    lw   $t0, 0($sp)   # Save $r2 to stack
    lw   $t1, 4($sp)   # Save $r3 to stack
    lw   $t2, 8($sp)   # Save $r4 to stack
    lw   $t3, 12($sp)   # Save $r4 to stack
    lw   $t4, 16($sp)   # Save $r4 to stack
    lw   $t5, 20($sp)   # Save $r4 to stack
    lw   $t6, 24($sp)   # Save $r4 to stack
    lw   $t7, 28($sp)   # Save $r4 to stack
    addi $sp, $sp, 68  # Increment stack pointer by 12
    ERET





/*********************************************************************
 * This is the actual interrupt handler that gets installed
 * in the interrupt vector table. It jumps to the T1 timer
 * interrupt handler function.
 ********************************************************************/
.section .vector_4, code
    j T1_ISR
    nop




