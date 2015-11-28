	.global start

	STACK = 01000
	rkda = 0177412

	.text
start:
	mov	$STACK,sp
	mov	$1,r1			/ r1 = block no = 1
rblk:
	clr	r0				/ r0 = 0
	div	$12,r0			/ r0 = r1/12, r1 = r1%12 
	ash	$4,r0			/ r0 = r0 << 4
	bis	r1,r0			/ r0 = r0
	mov	$rkda,r1	
	mov	r0,(r1)			/ *RKDA = r0
	mov	$02000,-(r1)	/ *RKBA = 02000
	mov	$-256,-(r1)		/ *RKWC = -256
	mov	$5,-(r1)		/ *RKCS = 5 (READ & GO)
1:
	tstb	(r1)		/ check *RKCS is ready
	bpl	1b

loop:
	br loop

	.end           
