.global _start

.section .text
_start:
    ! Load stack pointer
    mov.l   .L_stack_ptr, r15
    ! Call main
    mov.l   .L_main_ptr, r0
    jsr     @r0
    nop

_hang:
    bra     _hang
    nop

    .align 2
.L_stack_ptr:
    .long   0x8000
.L_main_ptr:
    .long   _main
