_out_port16: #out_port16(u16 portname,u16 valve)
    pushl %ebp
    movl %esp,%ebp

        movl %eax,.eax_d(,1)
        movl %edx,.edx_d(,1)

        .eax_d:
            .long 0x00
        .edx_d:
            .long 0x00
        .eax_sto:
            .long 0x00
        .edx_sto:
            .long 0x00

    movl 8(%ebp),%eax
    movl %eax,.eax_sto(,1)
    movl 12(%ebp),%eax
    movl %eax,.edx_sto(,1)

    movw .eax_sto(,1),%ax
    movw .edx_sto(,1),%dx

    outw %ax,%dx

            movl .eax_d(,1),%eax
            movl .edx_d(,1),%edx
    nop
    popl %ebp

    ret



_out_port8: #out_port8(u16 portname,u8 valve)
    pushl %ebp
    movl %esp,%ebp

        movl %eax,.eax_d(,1)
        movl %edx,.edx_d(,1)
            
    movl 8(%ebp),%eax
    movl %eax,.eax_sto(,1)
    movl 12(%ebp),%eax
    movl %eax,.edx_sto(,1)

    movw .eax_sto(,1),%ax
    movw .edx_sto(,1),%dx

    outb %al,%dx

            movl .eax_d(,1),%eax
            movl .edx_d(,1),%edx
    nop
    popl %ebp

    ret

_in_port16: #u16 in_port16(u16 portname)
    pushl %ebp
    movl %esp,%ebp

        movl %edx,.edx_d(,1)

        .eax_d:
            .long 0x00
        .edx_d:
            .long 0x00
        .edx_sto:
            .long 0x00
            
    movl 8(%ebp),%eax
    movl %eax,.edx_sto(,1)

    movw .edx_sto(,1),%dx

    outw %ax,%dx

            movl .edx_d(,1),%edx
    nop
    popl %ebp

    ret
