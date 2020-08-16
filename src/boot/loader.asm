; loader.asm

org 0x7e00

jmp StartLoader
nop

GDT_Begin: dd 0, 0
GDT_CodeSeg32 dd 0x0000ffff, 0xcf9a00
GDT_DataSeg32 dd 0x0000ffff, 0xcf9200
GDT_End: dd 0, 0

GDT_LEN equ GDT_End - GDT_Begin
GDT_PTR dw GDT_LEN
    dd GDT_Begin

[BITS 16]
StartLoader:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ax, 0x00
    mov ss, ax

    ; print Staring Loader...
    mov bx, MsgStartLoader
    mov cx, 26
    mov dx, 0300h
    call ShowMessage

    jmp $
    
    ; open A20 address
    mov ax,0x2401
    mov ax,0x180
    int 0x15
    jc OpenA20Fail

    mov ax,0x4f02
    int 13
    cli

    db 0x66
    lgdt [GDT_PTR]

    mov ax,0000000000001000b
    mov cs,ax
    mov ax,0000000000010000b
    mov ds,ax

    ; open protection mode
    mov eax, cr0
    or eax, 0x01
    mov cr0, eax

    sti

OpenA20Fail:
    mov bx, MsgOpenA20Fail
    mov cx, 33
    mov dx, 0x0400
    call ShowMessage
    jmp Fail

Fail:
    hlt
    jmp $

; cx: length, dh: row, dl: col, bx: string addr
ShowMessage:
    mov ax, ds
    mov es, ax
    mov bp, bx
    mov ax, 0x1301
    mov bx, 0x000f
    int 0x10
    ret

MsgStartLoader db "[loader] Staring Loader..."
MsgOpenA20Fail db "[loader] Open A20 address failed."

;times (0x7f7f - 19) db 0
times 1848 db 0