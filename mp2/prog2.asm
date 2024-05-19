;This program creates a postfix calculator
;When entering a number, the program push it to the stack
;When entering a operation, the program will pop two numbers and perform the operation
;If entered any invalid expression, program will print a invalid string and halt the program
;partners: wshen15, mcasper3
.ORIG x3000
	
;your code goes here
	
INITIALIZE			;Clear all registers
	AND R0, R0, #0
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0
	LEA R0, START_MESSAGE
	PUTS
INPUT				;Get the input and then evaluate
	;IN
	GETC
	OUT
	JSR EVALUATE

LOAD				;Load the value from the input register into R5 
	AND R5, R5, #0
	ADD R5, R5, R0
PRINT				;Print the hexadecimal output
	JSR PRINT_HEX
END
	HALT	

START_MESSAGE	.STRINGZ "Enter your postfix expression:  "	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	AND R3, R3, #0
	ADD R3, R3, R5	
	AND R6, R6, #0
	AND R1, R1, #0
	ADD R1, R1, #4
	ADD R6, R6, #4    ;Initialize bit counter to 4
EXTRACT
  AND R4, R4, #0 	;Clear bit storing register R4
  AND R2, R2, #0	;Clear bit counter R2
  ADD R2, R2, #4    ;Initialize bit counter to 4
 
CHECK_NUM
  ADD R3, R3, #0	;
  BRn NEGATIVE      ;Check if the number is negative, if so, branch to the operation
  BR NEXT_BIT		;Otherwise, go to the next bit

NEGATIVE
  ADD R4, R4, #1   ;If negative number, automatically add one to the bit storing register

NEXT_BIT
  ADD R3, R3, R3    ;Left shift R3
  ADD R2, R2, #-1   ;Decrement the bit counter
  BRz PRINT_HELP    ;If done, jump to printing process
  ADD R4, R4, R4    ;Left shift R4 for the next bit
  BR CHECK_NUM   	;Branch to check the next bit

PRINT_HELP
  ADD R0, R4, #-9   ;Subtract R4 by 9
  BRp LOAD_LETTER	;Check if R4>9, if so, load letters for correct hex value
  LD R0, ZERO     	;If not, load 0 into R0
  BR HEX			;Branch to get the correct hexidecimal

LOAD_LETTER
  LD R0, LETTER 	;Load 'A'-10 to R0

HEX ADD R0, R0, R4  ;Load the number in hex 
  	OUT				; Print out the number
	ADD R6, R6, #-1 ;Decrement the letter number counter
  	BRp EXTRACT		;Loop back if counter is still positive
	BR	END


LETTER .FILL x0037  ;'A'-10, so we can add to print out the correct hexadecimal
ZERO .FILL x0030  ;ascii code of '0'
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;R1 - 

EVALUATE
	ST R1, EVAL_SAVER1
	ST R2, EVAL_SAVER2
	ST R3, EVAL_SAVER3
	ST R4, EVAL_SAVER4
	ST R6, EVAL_SAVER6
	ST R7, EVAL_SAVER7		;Store origin values for all registers
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0			;Clear the registers for later use
CHECK_NUMBER				;Check if the input is a number
	LD R1, ASCII_ZERO		;Load R1 with the negative Ascii value of zero
	ADD R2, R0, R1			;Add negative ascii value and input in to temp register R2
	BRn CHECK_OPERATION		;If the input is less than ascii number of zero, then check if it is an operation
	ADD R2, R2, #-9			;Otherwise assume it is a number, subtract 9 to see if it is still positive
	BRp CHECK_OPERATION		;If it is still positive, check if the input is an operation
	ADD R0, R0, R1			;Otherwise it is a number
	JSR PUSH				;Push it to the stack
	BR INPUT				;Move on to the next input
CHECK_OPERATION				;Subroutine that checks if it is an operation
	
CHECK_PLUS					;Subroutine that checks if it is plus
	LD R1, ASCII_PLUS		;Same algorism as chekc numbers
	ADD R2, R1, R0
	BRnp CHECK_MINUS		;Branch to check minus sign if it isn't a plus sign
	JSR POP					;othewise pop two numbers
	ADD R4, R4, R0			;Put the popped number into R3 and R4 to perform the addition
	JSR POP	
	AND R5, R5, R5			;If can't pop(R5=1), then branch to the error message and halt the program
	BRp	ERROR
	ADD R3, R3, R0			;
	JSR PLUS				;JSR to the addition subroutine
	JSR PUSH				;Push the result
	BR INPUT				;Get the next input

CHECK_MINUS					;Check if the input is a minus sign, same algorism as CHECK_PLUS
	LD R1, ASCII_MINUS
	ADD R2, R1, R0
	BRnp CHECK_MUL			;If not a minus sign, check if it is a multiply sign
	JSR POP
	ADD R4, R4, R0
	JSR POP
	AND R5, R5, R5
	BRp	ERROR
	ADD R3, R3, R0			;Exact same method as CHECK_PLUS
	JSR MIN					;JSR to subtraction subroutine
	JSR PUSH				;Push the result
	BR INPUT				;Get the next input

CHECK_MUL					;Check if the input is "*", same algorism as above
	LD R1, ASCII_MUL
	ADD R2, R1, R0
	BRnp CHECK_DIV			;If not a multiplication sign, check if it a division
	JSR POP
	ADD R4, R4, R0
	JSR POP
	AND R5, R5, R5
	BRp	ERROR
	ADD R3, R3, R0
	JSR MUL
	JSR PUSH
	BR INPUT

CHECK_DIV					;Check if the operation is division, same algorism as above
	LD R1, ASCII_DIV
	ADD R2, R1, R0
	BRnp CHECK_POW			;If it isn't division, check if it is power
	JSR POP
	ADD R4, R4, R0
	JSR POP
	AND R5, R5, R5
	BRp	ERROR
	ADD R3, R3, R0
	JSR DIV
	JSR PUSH
	BR INPUT

CHECK_POW					;Check if the operation is power, same method as above
	LD R1, ASCII_POW
	ADD R2, R1, R0
	BRnp CHECK_EQUL			;If not a power operation, check if it is a equal sign
	JSR POP
	ADD R4, R4, R0
	JSR POP
	AND R5, R5, R5
	BRp	ERROR
	ADD R3, R3, R0
	JSR EXP
	JSR PUSH
	BR INPUT

CHECK_EQUL					;Check if input is a equal sign
	LD R1, ASCII_EQUL
	ADD R2, R1, R0
	BRnp CHECK_SPACE		;If not, check if input is a space
	AND R5, R5, #0
	JSR POP					;Otherwise pop the number on the stack
	AND R5, R5, R5
	BRp	ERROR				;If can't pop the number, branch to error
	LD R3, STACK_TOP
	LD R4, STACK_START
	NOT R4, R4
	ADD R4, R4, #1
	ADD R4, R3, R4
	BRnp ERROR				;If stack top doesn't equal to stack bottom, there is an error
	BR LOAD					;Otherwise branch to LOAD

CHECK_SPACE					;Check if the input is a space
	LD R1, ASCII_SPACE
	ADD R2, R1, R0
	BRz INPUT				;If it is, get the next input

ERROR						;Prints the error message
	LEA R0, ERROR_MESSAGE
	PUTS
	LD R1, EVAL_SAVER1
	LD R2, EVAL_SAVER2
	LD R3, EVAL_SAVER3
	LD R4, EVAL_SAVER4
	LD R6, EVAL_SAVER6
	LD R7, EVAL_SAVER7		;Load everything back to every registers
	BR END					;Branch to end of the program

DONE_EVAL					;End of evaluation method, load everything back to every registers
	LD R1, EVAL_SAVER1
	LD R2, EVAL_SAVER2
	LD R3, EVAL_SAVER3
	LD R4, EVAL_SAVER4
	LD R6, EVAL_SAVER6
	LD R7, EVAL_SAVER7
	RET						;Return the program

ERROR_MESSAGE	.STRINGZ "Invalid Expression"	;Invalid input string
EVAL_SaveR1	.BLKW #1
EVAL_SaveR2	.BLKW #1
EVAL_SaveR3	.BLKW #1
EVAL_SaveR4	.BLKW #1
EVAL_SaveR6	.BLKW #1
EVAL_SaveR7	.BLKW #1						;memory space to save registers
;your code goes here
	
ASCII_PLUS	.FILL #-43
ASCII_MINUS	.FILL #-45
ASCII_MUL	.FILL #-42
ASCII_DIV	.FILL #-47
ASCII_EQUL	.FILL #-61
ASCII_SPACE .FILL #-32
ASCII_ZERO	.FILL #-48
ASCII_NINE	.FILL #-57
ASCII_POW	.FILL #-94						;Negative ascii codes for operations and numbers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS										;Addition subroutine
;your code goes here
	AND R0, R0, #0							;Clear the output register
	ADD R0, R3, R4							;Do the addition
	RET										;return the program
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN											;Subtraction subroutine
;your code goes here
	ST R4, MIN_SAVER4						;Store origin R4 value into the memory
	AND R0, R0, #0
	NOT R4, R4
	ADD R4, R4, #1							;negate R4
	ADD R0, R3, R4							;Do the operation
	LD R4, MIN_SAVER4						;Load back the register values
	RET										;Return the program

MIN_SaveR4	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL											;Multiplication subroutinne
;your code goes here
	ST R4, MUL_SAVER4						;Store original R4 value into memory
	AND R0, R0, #0
	AND R4, R4, R4
	BRz MUL_DONE	
	AND R3, R3, R3
	BRz MUL_DONE							;If any operand is zero, branch to done and output is 0				
MUL_LOOP									;loop of addition
	ADD R0, R0, R3							
	ADD R4, R4, #-1							;Add and decrement R4 until it reaches 0
	BRp MUL_LOOP
MUL_DONE									;When R4 reaches 0, load the origin R4 value and then return
	LD R4, MUL_SAVER4
	RET

MUL_SaveR4	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0, remainder in R1
DIV											;Division subroutine
;your code goes here
	ST R1, DIV_SAVER1
	ST R4, DIV_SAVER4						;Save original value if R1 abd R4
	AND R4, R4, R4
	BRz	DIV_BY_ZERO							;Divide by zero case
	AND R0, R0, #0
	AND R1, R1, #0
	ADD R1, R1, R3							;Load R3 into R1
	NOT R4, R4
	ADD R4, R4, #1							;Invert R4 and start the loop
DIV_LOOP									;Division loop
	ADD R0, R0, #1							;Increment the quotient	
	ADD R1, R1, R4							;Subtract the quotient from the current remainder
	BRzp DIV_LOOP							;Loop when the current remainder is greater than zero
	NOT R4, R4	
	ADD R4, R4, #1							;Invert R4 to restore the original value of R4
	ADD R1, R1, R4							;Restore R1
	ADD R0, R0, #-1							;Restore R0
DIV_DONE
	LD R1, DIV_SAVER1
	LD R4, DIV_SAVER4
	RET										;Restore registers and return
DIV_BY_ZERO									;Divide by zero case, branch to error message
	BR	ERROR

DIV_SaveR1	.BLKW #1
DIV_SaveR4	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP											;Power operation subroutine
;your code goes here
	AND R0, R0, #0								
	AND R6, R6, #0							;Clear both R0 and R6 for later use
	ST R1, EXP_SAVER1
	ST R4, EXP_SAVER4
	ST R6, EXP_SAVER6
	ST R7, EXP_SAVER7						;Store original values for R1, R4, R6, and R7
	AND R4, R4, R4				
	BRz	EXP_ZERO							;Check if dealing with power of zero
	AND R1, R1, #0							;Clear R1
	ADD R6, R6, R4							;Store the power in R6
	ADD R6, R6, #-1							;Decrement R6 to deal with off by one
	AND R4, R4, #0							;Clear R4 and add the base
	ADD R4, R4, R3	
	ADD R1, R1, R4							;Store the base in R1 as well							
EXP_CALC									;Exponent calculation, JSR to multiplication loop
	JSR MUL_LOOP
	AND R3, R3, #0
	ADD R3, R3, R0							;Update the current value into R3
	AND R0, R0, #0							;Clear R0 for next output
	ADD R4, R4, R1							;Restore R4
	ADD R6, R6, #-1							;Decrement the counter
	BRp EXP_CALC							;If counter is positive, loop around the calculation
	ADD R0, R0, R3							;Else, store final result in R0
DONE_EXP									;End of exponent subroutine
	LD R1, EXP_SAVER1						;Restore all registers and return
	LD R4, EXP_SAVER4
	LD R6, EXP_SAVER6
	LD R7, EXP_SAVER7
	RET	
EXP_ZERO									;0 power case, always return 1
	ADD R0, R0, #1
	BR DONE_EXP
EXP_SaveR1	.BLKW #1
EXP_SaveR4	.BLKW #1
EXP_SaveR6	.BLKW #1
EXP_SaveR7	.BLKW #1
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
