;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Author : John Allard
; CE12, Lab #3   
; Oct 28th, 2014
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; R0 - General temporary value holder
;; R1 - Number of words to analyze (value at x3100)
;; R2 - Holds constant value 16
;; R3 - Outer-loop counter, goes from 0 to R1
;; R4 - Inner-loop counter, goes from 0 to 16 (R2)
;; R5 - Global counter of the number of 1's
;; R6 - Stores the value 3200, the starting address of the data
;; R7 - Holds the value of the current word we are evaluating (address)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


     .orig x3000
      
      LD R2 WSIZE       ;Load the word size into R2 (16 bits)

      LD R1 NUM         ;R1 contains 3100

      LD R6 START       ;3200, the address we start from

      LDR R1 R1 #0      ;Put value at x3100 into R1
      
      AND R3 R3 #0      ;initialize outer-loop counter

      AND R5 R5 #0      ;intitialize 1's counter

loop1 AND R4 R4 #0      ;initialize the inner loop counter to zero

      LDR R7 R6 #0      ;load the value at 3200+x into R7, where x is going to be incremented


loop2 ADD R7 R7 #0      ; All this does is force the computer to set the conditional flags based on the 
                        ;R7 register instead of another previous result.
      
      BRN INC           ;If R7 is negative, high bit is one, so increment counter

      BR BSFT           ;Perform a bitshift


INC   ADD R5 R5 #1      ;Increment the global counter
   
      BR BSFT           ;Go to shift the bits
      
     
 
BSFT  ADD R7 R7 R7      ;Double the R7 value, shifting the bits to the left 
      
      ADD R4 R4 #1      ;Increment Inner Counter

      NOT R0 R2         ;Invert 16

      ADD R0 R0 #1      ;Add 1 to make two's compliment -16

      ADD R0 R4 R0      ;Subtract 16 from our inner counter

      BRNZ loop2         ;If it's negative or zero then we need more iterations, if it is positive we have done 16 iterations and can go to the next outer loop


      ADD R3 R3 #1      ;Increment outerloop counter

      ADD R6 R6 #1      ;Go to the next x320c address

      NOT R0 R1         ;Invert value at x3100 (number of words to count)

      ADD R0 R0 #1      ;Add 1 to create -R1

      ADD R0 R3 R0      ;Subtract the number of words to count from the words we have counted to so far

      BRN loop1         ;If negative we still have more words to count

      LD R0 WRITE       ;Load x3101 into R0 (write address)

      STR R5 R0 #0       ;Store the final count value at address x3101

      

HALT

NUM   .fill x3100
WRITE .fill x3101
START .fill x3200
WSIZE .fill x000f

.END