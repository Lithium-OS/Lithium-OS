; loader.asm

org 0x8200

jmp StartLoader
nop

GDT_Begin: dd 0, 0
GDT_CodeSeg32 dd 0x0000ffff, 0xcf9a00
GDT_DataSeg32 dd 0x0000ffff, 0xcf9200
GDT_End: dd 0, 0

GDT_LEN equ GDT_End - GDT_Begin
GDT_PTR dw GDT_LEN
    dd GDT_Begin

MsgOpenA20Fail db "Open A20 Address Fail"

[BITS 16]
StartLoader:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ax, 0x00
    mov ss, ax

    ; open A20 address
    mov ax,0x2401
    int 0x15
    jc OpenA20Fail

    cli

    db 0x66
    lgdt [GDT_PTR]

    ; open protection mode
    mov eax, cr0
    or eax, 0x01
    mov cr0, eax

OpenA20Fail:
    mov bx, MsgOpenA20Fail
    mov cx, 0x15
    mov dx, 0x0100
    call ShowMessage
    jmp Fail

Fail:
    hlt
    jmp Fail

; cx: length, dh: row, dl: col, bx: string addr
ShowMessage:
    mov ax, ds
    mov es, ax
    mov bp, bx
    mov ax, 0x1301
    mov bx, 0x000f
    int 0x10
    ret

times 0x7f7f db 0
