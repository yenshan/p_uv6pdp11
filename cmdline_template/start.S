	.global start
	.global _cstart

	STACK = 0x1000

	.text
start:
	mov     $STACK, sp
	jsr     pc, _cstart
	halt

	.end           
