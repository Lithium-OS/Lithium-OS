org 0x7e00

mov cx,16
mov dh,0x03
mov dl,0x00
mov bx,Getmsg
call ShowMessage
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
Getmsg: ;16
    db "[Loader]Get SIG."
times 932-($$-$) db 0x00