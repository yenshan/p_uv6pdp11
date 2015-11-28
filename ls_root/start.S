	.GLOBAL _cstart

	STACK = 24*2048-514

	.text
	.even
	.globl	start
start:
	mov     $STACK, sp
	jsr     pc, _cstart
	mov     $start,-(sp)
	clr     pc

	.end           
