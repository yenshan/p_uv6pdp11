    .GLOBAL start
    .GLOBAL _cstart

    .text
start:
    mov     $0x1000, sp
    jsr     pc, _cstart
    .end           
