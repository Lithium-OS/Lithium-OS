org 0x7e00

mov cx,19
mov dh,0x03
mov dl,0x00
mov bx,Getmsg
call ShowMessage
; open A20 address
mov ax,0x2401
mov ax,0x180
int 0x15
jc Oa20F
call Oa20OK
jmp $
Oa20F:
mov cx,21
mov dh,0x04
mov dl,0x00
mov bx,Oa20F
call ShowMessage
Oa20OK:
mov cx,19
mov dh,0x04
mov dl,0x00
mov bx,Oa20OKmsg
call ShowMessage
ret
; cx: length, dh: row, dl: col, bx: string addr
ShowMessage:
    mov ax, ds
    mov es, ax
    mov bp, bx
    mov ax, 0x1301
    mov bx, 0x000f
    int 0x10
    ret
Getmsg: ;19
    db "[Loader]Get Signal."
Oa20Fmsg: ;21
    db "[Loader]Cannot Open A20."
Oa20OKmsg:;19
    db "[Loader]Opened A20."
times 760-($$-$) db 0x00