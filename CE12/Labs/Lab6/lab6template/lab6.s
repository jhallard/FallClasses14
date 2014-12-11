
#include <WProgram.h>

/* define all global symbols here */
.global T1Setup
.global T1Stop
.global T1Start
.global milliseconds

.text
.set noreorder

/*********************************************************************
 * Start Timer 1
 ********************************************************************/
.ent T1Start
T1Start:

.end T1Start

/*********************************************************************
 * Stop Timer 1
 ********************************************************************/
.ent T1Stop
T1Stop:

.end T1Stop


/*********************************************************************
 * Setup Timer 1 and interrupts (called it once)
 ********************************************************************/
.ent T1Setup
T1Setup:

.end T1Setup


/*********************************************************************
 * This is your ISR implementation. It is called from the vector table jump.
 ********************************************************************/
T1_ISR:


	
/*********************************************************************
 * This is the actual interrupt handler that gets installed
 * in the interrupt vector table. It jumps to the T1 timer
 * interrupt handler function.
 ********************************************************************/
.section .vector_4, code
	j T1_ISR
	nop


.data
milliseconds: .word 0
