.global _start

_start:
    ! Set stack pointer.
    mov.l   .L_stack, r15

    ! Call main
    mov.l   .L_main, r0
    jsr     @r0
    nop

! Infinite loop after main returns
_hang:
    bra _hang
    nop

.L_main:
.long   main

.L_stack:
.long   0x00008000
