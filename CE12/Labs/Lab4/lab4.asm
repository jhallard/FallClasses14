; @Author  - John H Allard Jr
; @file    - lab4.asm
; @date    - 11/10/2014
; @purpose - This is my LC3 assembly code for the lab #4 assignment for CE12 at UCSC during the Fall of 2014. This program can either 
;            encode or decode messages to/from morse code for the user. 


.ORIG x3000

START:

; clear all registers before use
AND R0, R0, 0
AND R1, R0, 0
AND R2, R0, 0
AND R3, R0, 0
AND R4, R0, 0

; Prompt the user for a character, either E/D
LEA R0, PROMPT1
PUTS
GETC

LD  R1, E
ADD R1, R1, R0
BRz ENCODE
LD R1, D
ADD R1, R1, R0
BRz DECODE

LEA R0, ERROR1
PUTS
BR START

ENCODE 
STI R0, ENCDEC ; store the users input char at x3200

DECODE
STI R0, ENCDEC ; store the users input char at x3200

; stop the processor
HALT



; subroutines



; data declarations follow below
; strings
PROMPT1: .STRINGZ "(E)ncode/(D)ecode : "
PROMPT2: .STRINGZ "Input Message : "
ERROR1: .STRINGZ "THAT IS AN ILLEGAL CHARACTER. PLEASE TRY AGAIN. \n"
ERROR2: .STRINGZ "THAT IS AN ILLEGAL STRING. PLEASE TRY AGAIN."
ERROR3: .STRINGZ "MESSAGE EXCEDES 30 CHARACTERS. PLEASE TRY AGAIN."


; memory locations
ENCDEC: .FILL x3200  ; location where we save the users E/D input char
INPUT: .BLKW #30     ;30 saved locations for the input chars
; variables
USERINPUT: .FILL 0
E:         .FILL #-69
D:         .FILL #-68
; end of code
.END