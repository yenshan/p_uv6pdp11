	.GLOBAL _cstart

	STACK = 07000 

	.text
	.even
	.globl	start
start:
	mov     $STACK, sp
	jsr     pc, _cstart
	mov     $start,-(sp)
	clr     pc

	.end           
