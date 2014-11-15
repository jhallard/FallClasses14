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
STI R0, ENCDEC  ; store the users input char at x3200

; Check if the input is either 'E' or 'D'
LD  R1, E
ADD R1, R1, R0
BRz STARTENCODE     ; if input is 'E', jump to encode
LD R1, D
ADD R1, R1, R0
BRz STARTDECODE     ; if input is 'D', jump to decode

LEA R0, ERROR1      ; else they entered an invalid character
PUTS
BR START            ; have the redo the input

STARTENCODE:
    LEA R0, PROMPT2 ; Prompt the user for the character string
    PUTS
    JSR GETASCII
    JSR PRINTENC
    BR FINISH

STARTDECODE:
    LEA R0, PROMPT2 ; Prompt the user for the character string
    PUTS
    JSR GETHEX
    JSR PRINTDEC
    BR FINISH

FINISH:
    ; stop the processor

HALT


 ;;;;;;;;;;;;;;;;;;;;;;;;;; First round of Data Declarations  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ;;;;;;;;;;;;;;;;;;;; These are used by routines that are in close proximity ;;;;;;;;;;;;;
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
MSGLENGTH: .FILL #31
NEWLINE:   .FILL #-10

; memory locations
ENCDEC: .FILL x3400  ; location where we save the users E/D input char
INPUT:  .FILL x3401  ; 30 saved locations for the input chars
OUTPUT:  .FILL x3421  ; 30 saved locations for the output chars
ENCBIT .FILL #0





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; SUBROUTINES ;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;; ERRORS AND PROMPTS ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PROMPTMSG2:
    LDI R0 ENCDEC
    LD  R1, E
    ADD R1, R1, R0
    BRz STARTENCODE     ; if input is 'E', jump to encode
    LD R1, D
    ADD R1, R1, R0
    BRz STARTDECODE     ; if input is 'D', jump to decode
    BR START


ERRMSG2:
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

ERRMSG3:
    LEA R0, ERROR3 ; Prompt the user for the character string
    PUTS
    LDI R0 ENCDEC
    LD  R1, E
    ADD R1, R1, R0
    BRz STARTENCODE     ; if input is 'E', jump to encode
    LD R1, D
    ADD R1, R1, R0
    BRz STARTDECODE     ; if input is 'D', jump to decode



GETHEXRET: .FILL x0000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;; GET HEX INPUT ;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GETHEX ;get a series of up to 30 characters representing hex digits
    ST R0 reg0;
    ST r1 reg1;
    ST R2 reg2;
    ST R3 reg3;
    ST R4 reg4;
    ST R5 reg5;
    ST R7, reg7

    ST R7, GETHEXRET

    LD R1, NUMCHARS ; Load the number of characters
    AND R2, R2, #0  ; Initialize Counter to zero
    LD R5, INPUT    ; Load the address x3201 to R5
    LD R3, OUTPUT

    GETHEXLOOP ; R4, R5 will hold each digit of the hex input
        GETC
        PUTC
        LD R4, NEWLINE
        ADD R4, R0, R4
        BRz GETHEXDONE  ; if the char is a newline escape the loop
        STR R0, R5, #0 ; store the char into memory
        ADD R5, R5, #1 ; Incrmement the memory location for the next str
        ADD R2, R2, #-1 ; increment counter
        ST R0, DECBIT1
 

        GETC
        PUTC
        LD R4, NEWLINE
        ADD R4, R0, R4
        BRz GETHEXDONE  ; if the char is a newline escape the loop
        STR R0, R5, #0 ; store the char into memory
        ADD R5, R5, #1 ; Incrmement the memory location for the next str

        ST R0, DECBIT2
        JSR DECODE
        LD R0, DECBIT1
        STR R0, R3, #0
        ADD R3, R3, #1
        ADD R2, R2, #-1 ; increment counter
        ADD R4, R2, R1 ; check if we have hit 31
        BRp GETHEXLOOP
        JSR ERRMSG3     ; if we made it this far we messed up

    GETHEXDONE
        LD R4, NEWLINE2
        STR R4, R3, #0 ;; store the final newline character
        LD R7, GETHEXRET
        LD R5, reg5
        LD R4, reg4
        LD R3, reg3
        LD R2, reg2
        LD R1, reg1
        LD R0, reg0
        RET



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;; GET ASCII INPUT ;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GETASCII: ; get a series of up to 30 ascii characters

    ST R0, reg0;
    ST R1, reg1;
    ST R2, reg2;
    ST R3, reg3;
    ST R4, reg4;
    ST R5, reg5;
    ST R7, reg7

    LD R1, MSGLENGTH ; Load the number of characters
    AND R2, R2, #0  ; Initialize Counter to zero
    LD R5, INPUT    ; Load the address x3201 to R5
    LD R3, OUTPUT

    ASCIILOOP: ; 
        GETC
        PUTC 
        LD R4, NEWLINE
        ADD R4, R0, R4
        BRz ASCIIDONE  ; if the char is a newline escape the loop
        STR R0, R5, #0 ; store the char into memory
        ADD R5, R5, #1 ; Incrmement the memory location for the next str
        ST R0, ENCBIT
        JSR ENCODE
        LD R0, ENCBIT
        STR R0, R3, #0
        ADD R3, R3, #1
        ADD R2, R2, #-1 ; increment counter
        ADD R0, R2, R1 ; check if we have hit 31
        BRp ASCIILOOP
        JSR ERRMSG3     ; if we made it this far we messed upII

    ASCIIDONE:
        LD R4, NEWLINE2
        STR R4, R3, #0 ;; store the final newline character
        LD R7, reg7
        LD R5, reg5
        LD R4, reg4
        LD R3, reg3
        LD R2, reg2
        LD R1, reg1
        LD R0, reg0

RET

NEWLINE2: .FILL #10
DECBIT1 .FILL #0
DECBIT2 .FILL #0



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
    ;ST R7, reg7

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
        ADD R1, R5, R2
        BRz ENCFOUND
        ADD R2, R2 #-1  ; increment the loop counter (count down)
        ADD R0, R0, #1 ; incrmement the address we are reading from
        ADD R1, R2, R3 ; see if we have checked all 10 available
        BRp NUMLOOP

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
        ADD R1, R5, R2
        BRz ENCFOUND
        ADD R2, R2 #-1  ; increment the loop counter
        ADD R0, R0, #1 ; incrmement the address we are reading from
        ADD R1, R2, R3 ; see if we have checked all 10 available
        BRp CHARLOOP

        JSR ERRMSG2     ; if we got here, the input was not valid



    ENCFOUND
        ;ADD R5, R4, #0 ; return the value via the R5 register
        ST R4, ENCBIT
        LD R0, reg0;
        LD R1, reg1;
        LD R2, reg2;
        LD R3, reg3;
        LD R4, reg4;
        LD R5, reg5;
        ;LD R7, reg7
RET










NINE:  .FILL x0039
NUMHEX:  .FILL #16 ; Number of unique hex numbers with 1 digit
NUMCHARS: .FILL #26 ; Number of letters in alphabet
NUMNUMS: .FILL #10 ; Decimal numbers (0-9)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;; MORSE CODE ;;;;;;;;;;;;;;;;;;
;;;;;;;;;;; LOOK-UP TABLE ;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

NUMS .FILL x0004 ; 0
     .FILL x0084 ; 1
     .FILL x00C4 ; 2
     .FILL x00E4 ; 3
     .FILL x00F4 ; 4
     .FILL x00FC ; 5
     .FILL x007C ; 6
     .FILL x003C ; 7
     .FILL x001C ; 8
     .FILL x000C ; 9

;;;;; Register Storage Destinations ;;;;
reg0:   .FILL x0000  ;
reg1:   .FILL x0000  ;
reg2:   .FILL x0000  ;
reg3:   .FILL x0000  ;
reg4:   .FILL x0000  ;
reg5:   .FILL x0000  ;
reg7:   .FILL x0000  ;


CHARS .FILL x00A0 ; A
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
ZERO:  .FILL x0030
EIGHT: .FILL x0008
OUTPUT1:  .FILL x3421  ; 30 saved locations for the output chars



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; DECODE FUNCTION ;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DECODE:  
    ST R0, reg0;
    ST R1, reg1;
    ST R2, reg2;
    ST R3, reg3;
    ST R4, reg4;
    ST R5, reg5;
    ;ST R7, reg7

    LD R5, DECBIT1 ; high bit
    ST R7, PRINTCHRET
    JSR CHAR2HEX
    LD R7, PRINTCHRET
    AND R1, R1, #0
    AND R2, R2, #0

    ADD R5, R5, #0
    BRz DB2

    DECLOOP:
    ADD R1, R1, #8
    ADD R1, R1, #8
    ADD R5, R5, #-1
    BRp DECLOOP

    DB2:
    LD R5, DECBIT2 ; high bit
    ST R7, PRINTCHRET
    JSR CHAR2HEX
    LD R7, PRINTCHRET

    ADD R5, R5, #0
    BRz CHECKNUMS1

    DECLOOP2:
    ADD R1, R1, #1
    ADD R5, R5, #-1
    BRp DECLOOP2

    ;;; Now R2 contains the number that the 2 digit hex value represents ;;;
    ;;; Example "1""A" = 16+10 = 26 ;;;;
    CHECKNUMS1
        LD R3, NUMNUMS ; LD -10 for the loop comparison
        AND R2, R2, #0 ; counter is R2
        LEA R0, NUMS   ; ADDRESS of nums

    NUMLOOP2
        LDR R4, R0, #0
        NOT R4, R4
        ADD R4, R4, #1
        ADD R4, R4, R1
        BRz DECFOUNDNUM
        ADD R2, R2 #-1  ; increment the loop counter (count down)
        ADD R0, R0, #1 ; incrmement the address we are reading from
        ADD R5, R2, R3 ; see if we have checked all 10 available
        BRp NUMLOOP2



        AND R3, R3, #0 ;NUMCHARS ; LD -10 for the loop comparison
        LD R3, NUMCHARS
        AND R2, R2, #0 ; counter is R2
        LEA R0, CHARS   ; ADDRESS of nums

    CHARLOOP2
        LDR R4, R0, #0
        NOT R4, R4
        ADD R4, R4, #1
        ADD R4, R4, R1
        BRz DECFOUNDCHAR
        ADD R2, R2 #-1  ; increment the loop counter
        ADD R0, R0, #1 ; incrmement the address we are reading from
        ADD R5, R2, R3 ; see if we have checked all 10 available
        BRp CHARLOOP2

        JSR ERRMSG2     ; if we got here, the input was not valid

    DECFOUNDNUM:
    LD R5, ZERO
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R5
    ST R2, DECBIT1
    LD R0, reg0;
    LD R1, reg1;
    LD R2, reg2;
    LD R3, reg3;
    LD R4, reg4;
    LD R5, reg5;
    RET

    DECFOUNDCHAR:
    LD R5, A
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R2, R5
    ST R2, DECBIT1
    LD R0, reg0;
    LD R1, reg1;
    LD R2, reg2;
    LD R3, reg3;
    LD R4, reg4;
    LD R5, reg5;
    RET

MSGLENGTH1: .FILL #30
REG7HOLD:   .FILL #0

PRINTDEC:
    ST R7, REG7HOLD
    LD  R3, OUTPUT1  ; Load add x3221
    LDR R0, R3, #0  ; Load value at x3221
    LD R4, NEWLINE1
    LD R1, MSGLENGTH1
    ADD R5, R4, R1
    BRz PRINTDECDONE

    AND R2, R2, #0
    

    PRINTDECLOOP:
    PUTC
    ADD R3, R3, #1
    LDR R0, R3, #0
    ADD R5, R4, R0
    BRz PRINTDECDONE
    ADD R2, R2, #-1
    ADD R5, R2, R1
    BRz PRINTDECDONE
    BR PRINTDECLOOP


PRINTDECDONE:
    LD R7, REG7HOLD
    RET



PRINTENC:
    LD  R3, OUTPUT1  ; Load add x3221
    LDR R1, R3, #0  ; Load value at x3221

    ;; This parts performs the equivilent of a bit shift to find the corresponding
    ;; character for the top 4 bits of the 8 bit morse code.
    PRINTENCLOOP:
    AND R5, R5, #0  ; Initialize Counter to zero
    AND R0, R0, #0
    LD R4, EIGHT      ; load 8
    ADD R4, R4, R4 ; load 16 (bit 5)
    AND R2, R4, R1 ; See if R1 has bit 5 high
    BRz NEXT1
    ADD R5, R5, #1
    NEXT1:
    LD R4, EIGHT      ; load 8
    ADD R4, R4, R4 ; load 16 (bit 5)
    ADD R4, R4, R4 ; load 32 (bit 6)
    AND R2, R4, R1 ; See if R1 has bit 5 high
    BRz NEXT2
    ADD R5, R5, #2
    NEXT2:
    LD R4, EIGHT      ; load 8
    ADD R4, R4, R4 ; load 16 (bit 5)
    ADD R4, R4, R4 ; load 32 (bit 6)
    ADD R4, R4, R4 ; load 64 (bit 6)
    AND R2, R4, R1 ; See if R1 has bit 5 high
    BRz NEXT3
    ADD R5, R5, #4
    NEXT3:
    LD R4,  EIGHT     ; load 8
    ADD R4, R4, R4 ; load 16 (bit 5)
    ADD R4, R4, R4 ; load 32 (bit 6)
    ADD R4, R4, R4 ; load 64 (bit 7)
    ADD R4, R4, R4 ; load 128 (bit 8)
    AND R2, R4, R1 ; See if R1 has bit 5 high
    BRz PRINTCHAR1
    ADD R5, R5, #8


    PRINTCHAR1:
        ST R7, PRINTCHRET
        JSR HEX2CHAR
        LD R7, PRINTCHRET
        ST R5  TEMPCHAR
        LD R0  TEMPCHAR
        ST R7, PRINTCHRET
        PUTC
        LD R7, PRINTCHRET

        ;; This part prints the second digit representing the lower 4 bits of the 8 bit morse code
        LDR R1, R3, #0 ; load the value at that address
        AND R4, R4, #0
        ADD R4, R4, #1
        ADD R4, R4, #2
        ADD R4, R4, #4
        ADD R4, R4, #8 ; R4 = 0x000f
        AND R5, R4, R1

        ST R7, PRINTCHRET
        JSR HEX2CHAR
        LD R7, PRINTCHRET
        ST R5  TEMPCHAR
        LD R0  TEMPCHAR
        ST R7, PRINTCHRET
        PUTC
        LD R7, PRINTCHRET
        ADD R3, R3, #1 ; incrmement to the next address
        LDR R1, R3, #0 ; load the value at that address
        LD R0 NEWLINE1  
        ADD R0, R0, R1
        BRnp PRINTENCLOOP ; if the next value is a newline then exit


    EXITPRINTCHAR:
        RET






PRINTCHRET .FILL x0000
TEMPCHAR: .FILL x0000
NEWLINE1: .FILL #-10




;; @Function CHAR2HEX
;; @Input    Character ascii code in R5
;; @Returns  Hex Number that the char represents, in R5 (example A -> #10, 0b1010)
CHAR2HEX:
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

    CHARHEXLOOP:
        LDR R4, R0, #0
        NOT R4, R4
        ADD R4, R4, #1
        ADD R4, R5, R4
        BRz FOUND1
        ADD R2, R2 #-1  ; increment the loop counter
        ADD R0, R0, #1 ; incrmement the address we are reading from
        ADD R1, R2, R3 ; see if we have checked all 16 available
        BRp CHARHEXLOOP

    FOUND1:
        NOT R2, R2
        ADD R2, R2, #1
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
HEX2CHAR:
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

    HEXCHARLOOP:
        LDR R4, R0, #0
        ADD R7, R5, R2
        BRz FOUND2
        ADD R2, R2 #-1  ; increment the loop counter
        ADD R0, R0, #1 ; incrmement the address we are reading from
        ADD R1, R2, R3 ; see if we have checked all 16 available
        BRp HEXCHARLOOP

        AND R5, R5 #0
        ADD R5, R5, #-1
        RET

    FOUND2:
        ADD R5, R4, #0 ; return the value via the R5 register
        LD R0, reg0;
        LD R1, reg1;
        LD R2, reg2;
        LD R3, reg3;
        LD R4, reg4;
        LD R7, reg7
RET

;; Used by the above two functions as a simple table that converts ascii hex values to binary numbers and vise versa
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