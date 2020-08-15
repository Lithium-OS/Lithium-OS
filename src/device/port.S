_out_port16: #out_port16(u16 portname,u16 valve)
    pushl %ebp
    movl %esp, %ebp
    movl 0xc(%ebp), %eax
    movl 0x8(%ebp), %edx
    outw %ax, %dx
    nop
    popl %ebp
    ret 

_out_port8: #out_port8(u16 portname,u8 valve)
    pushl %ebp
    movl %esp, %ebp
    movl 0xc(%ebp), %eax
    movl 0x8(%ebp), %edx
    outb %al, %dx
    nop
    popl %ebp
    ret

_in_port16: #u16 in_port16(u16 portname) 
    pushl %ebp
    movl %esp, %ebp
    movl 0x8(%ebp), %edx
    inw %dx, %ax
    andl 0xffff, %eax
    nop
    popl %ebp
    ret 

_in_port8: #u8 in_port16(u16 portname) 
    pushl %ebp
    movl %esp, %ebp
    movl 0x8(%ebp), %edx
    inb %dx, %al
    andl 0xff, %eax
    nop
    popl %ebp
    ret 
