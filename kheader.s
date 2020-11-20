.section .mbt2std
tag_start:
.long 0xE85250D6
.long 0
.long tag_end-tag_start
.long -1*(tag_end-tag_start + 0 +  0xE85250D6)

.vbe:
.short 5
.short 0
.long 20
.long 1024
.long 768
.long 32
.vbe_e:
.long 0
#.efi:
#.short 9
#.short 0
#.long 12
#.long 0x1000000
#.efi_e:
#.long 0
#.short 0
#.short 0
#.long 8
tag_end:
.long 0xffffffffffffffff

.section .text
_kstart:

    movl %ebx,%eax
    .lopsvge:
        addl $1,%ebx
        cmpl $0x7,(%ebx)
        jne .lopsvge
        cmpl $0x310,4(%ebx)
        jne .lopsvge
        addl $0x238,%ebx
    movl $0x5000,%ecx
    movl (%ebx),%edx
    /*
    .lop:
        movl $0x00ff0000,(%edx) #Red
        addl $0x4,%edx
        subl $1,%ecx
        cmp $1,%ecx
        jnz .lop
        movl $0x5000,%ecx
        jmp .lop1
    .lop1:
        movl $0x0000ff00,(%edx)#Green
        addl $0x4,%edx
        subl $1,%ecx
        cmp $1,%ecx
        jnz .lop1
        movl $0x5000,%ecx
        jmp .lop2
    .lop2:
        movl $0x000000ff,(%edx)#Blue
        addl $0x4,%edx
        subl $1,%ecx
        cmp $1,%ecx
        jnz .lop2
        movl $0x5000,%ecx
        jmp .lop3
    .lop3:
        movl $0x00ffff00,(%edx)#Yellow
        addl $0x4,%edx
        subl $1,%ecx
        cmp $1,%ecx
        jnz .lop3
        movl $0x5000,%ecx
        jmp .lop4
    .lop4:
        movl $0x0000ffff,(%edx)#Cyan
        addl $0x4,%edx
        subl $1,%ecx
        cmp $1,%ecx
        jnz .lop4
        movl $0x5000,%ecx
        jmp .lop5
    .lop5:
        movl $0x00ff00ff,(%edx)#Pink
        addl $0x4,%edx
        subl $1,%ecx
        cmp $1,%ecx
        jnz .lop5
        movl $0x5000,%ecx    
        
        

*/
lidt (idtrp)
jmp kmain
idt_s:
sys_idt: .fill 512,8,0 
idt_e:
idtrp:
    .word idt_e - idt_s - 1
    .long sys_idt
    
.globl _kstart
.globl sys_idt
