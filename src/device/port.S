_out_port16: #out_port16(u16 portname,u16 valve)
    pushl %ebp
    movl %esp,%ebp

        movl %eax,[.eax_d]
        movl %edx,[.edx_d]

        .eax_d:
            .long 0x00
        .edx_d:
            .long 0x00
        .eax_sto:
            .long 0x00
        .edx_sto:
            .long 0x00

    movl 8(%ebp),%eax
    movl %eax,[.eax_sto]
    movl 12(%ebp),%eax
    movl %eax,[.edx_sto]

    movw [.eax_sto],%ax
    movw [.edx_sto],%dx

    outw %ax,%dx

            movl [.eax_d],%eax
            movl [.edx_d],%edx
    nop
    popl %ebp

    ret



_out_port8: #out_port8(u16 portname,u8 valve)
    pushl %ebp
    movl %esp,%ebp

        movl %eax,[.eax_d]
        movl %edx,[.edx_d]

        .eax_d:
            .long 0x00
        .edx_d:
            .long 0x00
        .eax_sto:
            .long 0x00
        .edx_sto:
            .long 0x00
            
    movl 8(%ebp),%eax
    movl %eax,[.eax_sto]
    movl 12(%ebp),%eax
    movl %eax,[.edx_sto]

    movw [.eax_sto],%ax
    movw [.edx_sto],%dx

    outb %al,%dx

            movl [.eax_d],%eax
            movl [.edx_d],%edx
    nop
    popl %ebp

    ret

