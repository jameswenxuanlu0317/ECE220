;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; partners: wshen15, mcasper3

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;Intro Paragraph: This program prints out the histogram.
; 				By loading the letters first and then converting the numbers into 4 bit hex,
;				it will print out a historgram in the right format
;				By incrementing and adding letter offset after each letter is done,
;				It will move on in alphabetical order until line counter reaches 0
;				
;				Table of Registers:
;									R0: printer register
;									R1: Letter offset
;									R2: Bit counter 
;									R3: Line counter
;									R4: Each bit from histogram
;									R5: letter counter
;									R6: Histogram

CLEAR
  AND R1,R1,#0
  AND R2,R2,#0
  AND R3,R3,#0		
  AND R4,R4,#0
  AND R5,R5,#0
  AND R6,R6,#0		;Clear all registers 

LINE_COUNT  
	LD R3, NUM_BINS   ;Load 27 into the line counter
LETTER_THEN_NUMBER
  LD R0, AT			;Load '@' into R0
  ADD R0, R0, R1    ;add the letter offset to R0
  OUT               ;Print out the letter 
  LD R0, SPACE      ;
  OUT				;Print out a space 
  LD R6, HIST_ADDR  ;Load the histogram into R6
  ADD R6, R6, R1    ;ADD the letter offset on R6 to get to the right letter place
  ST R6, TEMP  		;Store R6 to a temporary space in to the memory
  LDI R6, TEMP 		;Get the content in R6 by loading it from the memory
  ADD R5, R5, #4    ;Initialize bit counter to 4

EXTRACT
  AND R4, R4, #0 	;Clear bit storing register R4
  AND R2, R2, #0	;Clear bit counter R2
  ADD R2, R2, #4    ;Initialize bit counter to 4
 
CHECK_NUMBER
  ADD R6, R6, #0	;
  BRn NEGATIVE      ;Check if the number is negative, if so, branch to the operation
  BR NEXT_BIT		;Otherwise, go to the next bit

NEGATIVE
  ADD R4, R4, #1   ;If negative number, automatically add one to the bit storing register

NEXT_BIT
  ADD R6, R6, R6    ;Left shift R6
  ADD R2, R2, #-1   ;Decrement the bit counter
  BRz PRINT         ;If done, jump to printing process
  ADD R4, R4, R4    ;Left shift R4 for the next bit
  BR CHECK_NUMBER   ;Branch to check the next bit

PRINT
  ADD R0, R4, #-9   ;Subtract R4 by 9
  BRp LOAD_LETTER	;Check if R4>9, if so, load letters for correct hex value
  LD R0, ZERO     	;If not, load 0 into R0
  BR HEX			;Branch to get the correct hexidecimal

LOAD_LETTER
  LD R0, LETTER 	;Load 'A'-10 to R0
HEX ADD R0, R0, R4  ;Load the number in hex 
  OUT				; Print out the number
  ADD R5, R5, #-1   ;Decrement the letter number counter
  BRp EXTRACT		;Loop back if counter is still positive
  LD R0, NEWLINE    ;Load R0 with new line 
  OUT				;Print a new line
  ADD R1, R1, #1	;Increment the letter offset
  ADD R3, R3, #-1   ;Decrement line counter 
  BRp LETTER_THEN_NUMBER   ;If line counter still positive, loop back all the way to the start


DONE	HALT			; done

NEWLINE .FILL x000A ;newline character
AT .FILL x0040  ;'@' character
ZERO .FILL x0030  ;ascii code of '0'
LETTER .FILL x0037  ;'A'-10, so we can add to print out the correct hexadecimal
SPACE  .FILL x0020  ;' '
TEMP .BLKW #1
; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
