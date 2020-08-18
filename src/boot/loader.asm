; loader.asm

org 0x7e00

jmp StartLoader
nop

GDT_Begin: dd 0, 0
                            ;Data R/W 4KiB Kernel Base:0 Limit:512MiB               0x08
GDT_Kernel_dataSect:    dq 00000000_1100_0010_10010010_00000000_0000000000000000_0000000000000000b
                            ;Code ExecOnly 4KiB Kernel Base:0 Limit:512MiB          0x10
GDT_Kernel_codeSect:    dq 00000000_1100_0010_10011000_00000000_0000000000000000_0000000000000000b
                            ;Stack R/W 4KiB User Base:512MiB limit:640MiB           0x18
GDT_User_stackSect:     dq 00000000_1100_0010_11110110_00000010_0000000000000000_1000000000000000b
                            ;Stack R/W 4KiB Kernel Base:642MiB limit:640MiB         0x20
GDT_Kernel_stackSect:   dq 00000000_1100_0010_11110110_00000010_1000001000000000_1000000000000000b
                            ;Data R/W 4KiB User Base:642MiB Limit:unlimited         0x28
GDT_User_dataSect:      dq 00000000_1100_1111_11110010_00000010_1000001000000000_1111111111111111b
                            ;Code ExecOnly 4KiB User Base:642MiB Limit:unlimited    0x30
GDT_User_codeSect:      dq 00000000_1100_1111_11111000_00000010_1000001000000000_1111111111111111b

GDT_End:
GDT_LEN equ GDT_End - GDT_Begin - 1
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

    
    ; open A20 address
    enable_A20
    mov bx, MagOpenA20OK
    mov cx, 26
    mov dx, 0400h
    call ShowMessage

    cli

    db 0x66
    lgdt [GDT_PTR]

    mov ax,0x10
    mov cs,ax
    mov ax,0x08
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

enable_A20:
        cli
 
        call    a20wait
        mov     al,0xAD
        out     0x64,al
 
        call    a20wait
        mov     al,0xD0
        out     0x64,al
 
        call    a20wait2
        in      al,0x60
        push    eax
 
        call    a20wait
        mov     al,0xD1
        out     0x64,al
 
        call    a20wait
        pop     eax
        or      al,2
        out     0x60,al
 
        call    a20wait
        mov     al,0xAE
        out     0x64,al
 
        call    a20wait
        sti
        ret
 
a20wait:
        in      al,0x64
        test    al,2
        jnz     a20wait
        ret
 
 
a20wait2:
        in      al,0x64
        test    al,1
        jz      a20wait2
        ret

MsgStartLoader db "[loader] Staring Loader..."
MsgOpenA20Fail db "[loader] Open A20 address failed."
MagOpenA20OK   db "[loader] Open A20 address OK.    "

times 1786 db 0
