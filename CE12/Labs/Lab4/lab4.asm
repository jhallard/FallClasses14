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
AND R5, R0, 0


; Prompt the user for a character, either E/D
LEA R0, PROMPT1
PUTS
GETC

; Check if the input is either 'E' or 'D'
LD  R1, E
ADD R1, R1, R0
STI R0, ENCDEC  ; store the users input char at x3200
BRz STARTENCODE     ; if input is 'E', jump to encode
LD R1, D
ADD R1, R1, R0
BRz STARTDECODE     ; if input is 'D', jump to decode
LEA R0, ERROR1 ; Else they entered an invalid character
PUTS
BR START        ; have the redo the input

STARTENCODE 
LEA R0, PROMPT2 ; Prompt the user for the character string
PUTS
JSR GETASCII
LD R5, EE
ST R5, ENCBIT
JSR ENCODE
LD R5, ENCBIT
BR FINISH

STARTDECODE
LEA R0, PROMPT2 ; Prompt the user for the character string
PUTS
JSR GETHEX
BR FINISH

FINISH
; stop the processor

HALT


; data declarations follow below
; strings
PROMPT1: .STRINGZ "(E)ncode/(D)ecode : "
E:         .FILL #-69
EE:        .FILL #69
D:         .FILL #-68
ERROR1:  .STRINGZ "\n THAT IS AN ILLEGAL CHARACTER. PLEASE TRY AGAIN. \n"
ERROR2:  .STRINGZ "\n THAT IS AN ILLEGAL STRING. PLEASE TRY AGAIN. \n"
ERROR3:  .STRINGZ "\n MESSAGE EXCEDES 30 CHARACTERS. PLEASE TRY AGAIN. \n"
PROMPT2: .STRINGZ "Input Message : "

; variables
USERINPUT: .FILL 0
NUMCHARS:  .FILL #-31
NEWLINE:   .FILL #-10

; memory locations
ENCDEC: .FILL x3200  ; location where we save the users E/D input char
INPUT:  .FILL x3201  ; 30 saved locations for the input chars
OUPUT:  .FILL x3221  ; 30 saved locations for the output chars
ENCBIT .FILL #0
DECBIT .FILL #0




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; subroutines ;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;; ERRORS AND PROMPTS ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PROMPTMSG2
LDI R0 ENCDEC
LD  R1, E
ADD R1, R1, R0
BRz STARTENCODE     ; if input is 'E', jump to encode
LD R1, D
ADD R1, R1, R0
BRz STARTDECODE     ; if input is 'D', jump to decode
BR START


ERRMSG2
LEA R0, ERROR2 ; Prompt the user for the character string
PUTS
LDI R0 ENCDEC
LD  R1, E
ADD R1, R1, R0
BRz STARTENCODE     ; if input is 'E', jump to encode
LD R1, D
ADD R1, R1, R0
BRz STARTDECODE     ; if input is 'D', jump to decode
BR START

ERRMSG3
LEA R0, ERROR3 ; Prompt the user for the character string
PUTS
LDI R0 ENCDEC
LD  R1, E
ADD R1, R1, R0
BRz STARTENCODE     ; if input is 'E', jump to encode
LD R1, D
ADD R1, R1, R0
BRz STARTDECODE     ; if input is 'D', jump to decode


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;; GET INPUT ;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GETHEX ;get a series of up to 30 characters representing hex digits
ST R0 reg0;
ST r1 reg1;
ST R2 reg2;
ST R3 reg3;
ST R4 reg4;
ST R5 reg5;
ST R7, reg7

LD R1, NUMCHARS ; Load the number of characters
AND R2, R2, #0  ; Initialize Counter to zero
LD R5, INPUT    ; Load the address x3201 to R5

GETHEXLOOP ; R4, R5 will hold each digit of the hex input
GETC
PUTC
LD R4, NEWLINE
ADD R4, R0, R4
BRz GETHEXDONE  ; if the char is a newline escape the loop
STR R0, R5, #0 ; store the char into memory
ADD R5, R5, #1 ; Incrmement the memory location for the next str
ADD R2, R2, #1 ; increment counter
ADD R3, R2, R1 ; check if we have hit 31
BRn GETHEXLOOP
JSR ERRMSG3     ; if we made it this far we messed up

GETHEXDONE
LD R7, reg7
LD R5, reg5
LD R4, reg4
LD R3, reg3
LD R2, reg2
LD R1, reg1
LD R0, reg0
RET



GETASCII ; get a series of up to 30 ascii characters

ST R0, reg0;
ST R1, reg1;
ST R2, reg2;
ST R3, reg3;
ST R4, reg4;
ST R5, reg5;
ST R7, reg7

LD R1, NUMCHARS ; Load the number of characters
AND R2, R2, #0  ; Initialize Counter to zero
LD R5, INPUT    ; Load the address x3201 to R5

ASCIILOOP ; 
GETC
PUTC 
LD R4, NEWLINE
ADD R4, R0, R4
BRz ASCIIDONE  ; if the char is a newline escape the loop
STR R0, R5, #0 ; store the char into memory
ADD R5, R5, #1 ; Incrmement the memory location for the next str
ADD R2, R2, #1 ; increment counter
ADD R3, R2, R1 ; check if we have hit 31
BRn ASCIILOOP
JSR ERRMSG3     ; if we made it this far we messed upII

ASCIIDONE
LD R7, reg7
LD R5, reg5
LD R4, reg4
LD R3, reg3
LD R2, reg2
LD R1, reg1
LD R0, reg0

RET




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; ENCODE FUNCTION ;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ENCODE
ST R0, reg0;
ST R1, reg1;
ST R2, reg2;
ST R3, reg3;
ST R4, reg4;
ST R5, reg5;
ST R7, reg7

LD R1, ZERO
LD R5, ENCBIT
NOT R1, R1
ADD R1, R1, #1
ADD R1, R1, R5
BRzp CHECKNUMS
JSR ERRMSG3


CHECKNUMS
LD R1, NINE
NOT R1, R1
ADD R1, R1, #1
ADD R1, R1, R5
BRp CHECKCHARS

LD R1, ZERO
NOT R1, R1
ADD R1, R1, #1
ADD R5, R5, R1

LD R3, NUMNUMS ; LD -10 for the loop comparison
AND R2, R2, #0 ; counter is R2
LEA R0, NUMS   ; ADDRESS of nums

NUMLOOP
LDR R4, R0, #0
ADD R7, R5, R2
BRz ENCFOUND
ADD R2, R2 #1  ; increment the loop counter
ADD R0, R0, #1 ; incrmement the address we are reading from
ADD R1, R2, R3 ; see if we have checked all 10 available
BRn NUMLOOP

JSR ERRMSG2     ; if we got here, the input was not valid


CHECKCHARS
LD R1, A
NOT R1, R1
ADD R1, R1, #1
ADD R1, R1, R5
BRzp CHECKCHARS2
JSR ERRMSG2

LD R1, Z
NOT R1, R1
ADD R1, R1, #1
ADD R1, R1, R5
BRnz CHECKCHARS2
JSR ERRMSG2

CHECKCHARS2
LD R1, A
NOT R1, R1
ADD R1, R1, #1
ADD R5, R5, R1

LD R3, NUMCHARS ; LD -10 for the loop comparison
AND R2, R2, #0 ; counter is R2
LEA R0, CHARS   ; ADDRESS of nums

CHARLOOP
LDR R4, R0, #0
NOT R1, R2
ADD R1, R1, #1
ADD R7, R5, R1
BRz ENCFOUND
ADD R2, R2 #1  ; increment the loop counter
ADD R0, R0, #1 ; incrmement the address we are reading from
ADD R1, R2, R3 ; see if we have checked all 10 available
BRn CHARLOOP

JSR ERRMSG2     ; if we got here, the input was not valid



ENCFOUND
ADD R5, R4, #0 ; return the value via the R5 register
ST R5, ENCBIT
LD R0, reg0;
LD R1, reg1;
LD R2, reg2;
LD R3, reg3;
LD R4, reg4;
LD R7, reg7
RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; DECODE FUNCTION ;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

reg0:   .FILL x0000  ;
reg1:   .FILL x0000  ;
reg2:   .FILL x0000  ;
reg3:   .FILL x0000  ;
reg4:   .FILL x0000  ;
reg5:   .FILL x0000  ;
reg7:   .FILL x0000  ;




NUMHEX:  .FILL #-16
NUMCHAR: .FILL #-26
NUMNUMS: .FILL #-10


NUMS .FILL x0084 ; 0
.FILL x00C4 ; 1
.FILL x00E4 ; 2
.FILL x00F4 ; 3
.FILL x00FC ; 4
.FILL x007C ; 5
.FILL x003C ; 6
.FILL x001C ; 7
.FILL x000C ; 8
.FILL x0004 ; 9


CHARS .FILL x00A0  ; A
.FILL x0078 ; B
.FILL x0058 ; C
.FILL x0070 ; D
.FILL x00C0 ; E
.FILL x00D8 ; F
.FILL x0030
.FILL x00F8
.FILL x00E0
.FILL x0088
.FILL x0050
.FILL x00B8
.FILL x0020
.FILL x0060
.FILL x0010
.FILL x0098
.FILL x0028
.FILL x00B0
.FILL x00F0
.FILL x0040
.FILL x00D0
.FILL x00E8
.FILL x0090 ; W
.FILL x0068 ; X
.FILL x0048 ; Y
.FILL x0038 ; Z

A: .FILL x0041
Z: .FILL x0050
ZERO .FILL x0030
NINE .FILL x0039






;; @Function CHAR2HEX
;; @Input    Character ascii code in R5
;; @Returns  Hex Number that the char represents, in R5 (example A -> #10, 0b1010)
CHAR2HEX
ST R0, reg0;
ST R1, reg1;
ST R2, reg2;
ST R3, reg3;
ST R4, reg4;
ST R5, reg5;
ST R7, reg7

LD R3, NUMHEX ; LD -16 for the loop comparison
AND R2, R2, #0 ; counter is R2
LEA R0, HEX

CHARHEXLOOP
LDR R4, R0, #0
NOT R4, R4
ADD R4, R4, #1
ADD R4, R5, R4
BRz FOUND1
ADD R2, R2 #1  ; increment the loop counter
ADD R0, R0, #1 ; incrmement the address we are reading from
ADD R1, R2, R3 ; see if we have checked all 16 available
BRn CHARHEXLOOP

FOUND1
ADD R5, R2, #0 ; return the value via the R5 register
LD R0, reg0;
LD R1, reg1;
LD R2, reg2;
LD R3, reg3;
LD R4, reg4;
LD R7, reg7
RET

;; @Function HEX2CHAR
;; @Input    Single hex digit (0x00-0x0F) in R5
;; @Returns  ASCII value that corresponds to the hex digit (ex 0x0C -> 'C' -> 0x43)
HEX2CHAR
ST R0, reg0;
ST R1, reg1;
ST R2, reg2;
ST R3, reg3;
ST R4, reg4;
ST R5, reg5;
ST R7, reg7

LD R3, NUMHEX ; LD -16 for the loop comparison
AND R2, R2, #0 ; counter is R2
LEA R0, HEX

HEXCHARLOOP
LDR R4, R0, #0
NOT R1, R2
ADD R1, R1, #1
ADD R7, R5, R1
BRz FOUND2
ADD R2, R2 #1  ; increment the loop counter
ADD R0, R0, #1 ; incrmement the address we are reading from
ADD R1, R2, R3 ; see if we have checked all 16 available
BRn HEXCHARLOOP

FOUND2
ADD R5, R4, #0 ; return the value via the R5 register
LD R0, reg0;
LD R1, reg1;
LD R2, reg2;
LD R3, reg3;
LD R4, reg4;
LD R7, reg7
RET

;; Used by the above two functions as a simple table

HEX .FILL x0030
.FILL x0031
.FILL x0032
.FILL x0033
.FILL x0034
.FILL x0035
.FILL x0036
.FILL x0037
.FILL x0038
.FILL x0039
.FILL x0041
.FILL x0042
.FILL x0043
.FILL x0044
.FILL x0045
.FILL x0046

; end of code
.END