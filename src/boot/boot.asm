;===写死的文件长度,注意更改!
org 0x7c6a

ReadSymPacket2:
db 0x10 ;32bit wide
db 0x00 ;Rev
dw 0x64 ;64 Sector
dd 0x7e00 
dq 0x04128 ;No.4128 Sector
CNT:
dw 0x00
StartBoot:
    mov ah,0x41
    mov ax,0x55aa
    mov al,0x80
    int 0x13
    jc lbaFail
    jnc lbaload
chsload:
    mov ax,0x0000
    mov es,ax
    mov ah,0x02
    mov al,1
    mov ah,0
    mov ch,0
    mov cl,398
    mov dh,0
    mov dl,0x80
    mov bx,0x7e00
    int 0x13
    cmp ah,0x00
    cmp al,1
    jne chsfail
    je chsok
lbaload:
    mov ah,0x42
    mov si,ReadSymPacket2 ;读loader
    int 0x13  
    jc lldrFail
lloader:
    jmp 0x7e00
lldrFail:
    mov bx, ldrFailmsg
    mov cx, 30
    mov dx, [CNT]
    add dx,0x100
    mov [CNT],dx
    call ShowMessage
    jmp $
lbaFail:
    mov bx, lbaFailmsg
    mov cx, 28
    mov dx, [CNT]
    add dx,0x100
    mov [CNT],dx
    call ShowMessage
    jmp chs
chs:
    mov bx, chslldrmsg
    mov cx, 29
    mov dx, [CNT]
    add dx,0x100
    mov [CNT],dx
    call ShowMessage
    jmp chsload
chsfail:
    mov bx, chslfaimsg
    mov cx, 30
    mov dx, [CNT]
    add dx,0x100
    mov [CNT],dx
    call ShowMessage
    jmp $
chsok:
    mov bx, chsldokmsg
    mov cx, 16
    mov dx, [CNT]
    add dx,0x100
    mov [CNT],dx
    call ShowMessage
    jmp 0x0000:0x7e00
; cx: length, dh: row, dl: col, bx: string addr
ShowMessage:
    push eax
    mov ax, ds
    mov es, ax
    mov bp, bx
    mov ax, 0x1301
    mov bx, 0x000f
    int 0x10
    pop eax
    ret

ldrFailmsg db "[boot] LBA Load Loader failed."
lbaFailmsg db "[boot] Cannot found LBAbios."
chslldrmsg db "[boot] Try to use C/H/S Mode."
chslfaimsg db "[boot] CHS Load Loader failed."
chsldokmsg db "[boot] C/H/S OK."
