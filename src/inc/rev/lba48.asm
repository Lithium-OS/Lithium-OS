;栈传参,先后压入:16b高扇区号,32b低扇区号,16b扇区数,目的地址
LBA48ReadSector:
    .RevLBA48ReadregEbx:
        dd 0x00
    .RevLBA48ReadregEcx:
        dd 0x00
    .RevLBA48ReadregEdx:
        dd 0x00
    .RevLBA48ReadregEax:
        dd 0x00
    mov [.RevLBA48ReadregEbx],ebx
    mov [.RevLBA48ReadregEcx],ecx
    mov [.RevLBA48ReadregEdx],edx
    mov [.RevLBA48ReadregEax],eax

    call LBAwaitIdel

    pop ebx
    pop cx
    pop edx
    pop ax

    push edx
    push eax
    mov dx,0x1f1
    mov al,0
    out dx,al
    out dx,al
    pop eax
    pop edx

    push eax
    push edx
    mov dx,0x1f2
    mov al,ch
    out dx,al ;第一次要读的扇区数的高8位,第二次低8位
    mov al,cl
    out dx,al
    pop edx
    pop eax

    push edx
    push eax
    mov eax,edx
    mov dx,0x1f3
    shr eax,24
    out dx,al ;LBA参数的24~31位
    pop eax
    pop edx

    push edx
    push eax
    mov eax,edx
    mov dx,0x1f3
    out dx,al ;LBA参数的0~7位
    pop eax
    pop edx

    push edx
    push eax
    mov dx,0x1f4
    out dx,al ;LBA参数的32~39位
    pop eax
    pop edx

    push edx
    push eax
    mov eax,edx
    mov al,ah
    mov dx,0x1f4
    out dx,al ;LBA参数的8~15位
    pop eax
    pop edx

    push edx
    push eax
    mov al,ah
    mov dx,0x1f5
    out dx,al ;LBA参数的40~47位
    pop eax
    pop edx

    push edx
    push eax
    mov eax,edx
    shr eax,16
    mov dx,0x1f5
    out dx,al ;LBA参数的16~23位
    pop eax
    pop edx

    push edx
    push eax
    mov dx,0x1f6
    mov al,01000000b ;MasterDsk
    out dx,al
    pop eax
    pop edx

    push edx
    push eax
    mov dx,0x1f7
    mov al,0x24 ;Read
    out dx,al
    pop eax
    pop edx
    
    mov ax,cx
    mul WORD 32
    shl eax,[SYM_LBA48_ASM_WORD_PER_SECTOR]
    mov ax,dx
    mov dx,0x1f0
    mov ecx,eax
    .LBA48ReadSector:
    in ax,dx
    mov [ebx],ax
    add ebx,2
    sub ecx,1
    cmp ecx,0
    jne .LBA48ReadSector
    nop
    nop
    ret

    
    
    mov ebx,[.RevLBA48ReadregEbx]
    mov ecx,[.RevLBA48ReadregEcx]
    mov edx,[.RevLBA48ReadregEdx]
    mov eax,[.RevLBA48ReadregEax]

;[Not Finish]栈传参,先后压入:16b高扇区号,32b低扇区号,16b扇区数,目的地址
LBA48WriteSector:
    .RevLBA48WriteregEbx:
        dd 0x00
    .RevLBA48WriteregEcx:
        dd 0x00
    .RevLBA48WriteregEdx:
        dd 0x00
    .RevLBA48WriteregEax:
        dd 0x00
    mov [.RevLBA48WriteregEbx],ebx
    mov [.RevLBA48WriteregEcx],ecx
    mov [.RevLBA48WriteregEdx],edx
    mov [.RevLBA48WriteregEax],eax

    call LBAwaitIdel

    pop ebx
    pop cx
    pop edx
    pop ax

    push edx
    push eax
    mov dx,0x1f1
    mov al,0
    out dx,al
    out dx,al
    pop eax
    pop edx


    push eax
    push edx
    mov dx,0x1f2
    mov al,ch
    out dx,al ;第一次要读的扇区数的高8位,第二次低8位
    mov al,cl
    out dx,al
    pop edx
    pop eax

    push edx
    push eax
    mov eax,edx
    mov dx,0x1f3
    shr eax,24
    out dx,al ;LBA参数的24~31位
    pop eax
    pop edx

    push edx
    push eax
    mov eax,edx
    mov dx,0x1f3
    out dx,al ;LBA参数的0~7位
    pop eax
    pop edx

    push edx
    push eax
    mov dx,0x1f4
    out dx,al ;LBA参数的32~39位
    pop eax
    pop edx

    push edx
    push eax
    mov eax,edx
    mov al,ah
    mov dx,0x1f4
    out dx,al ;LBA参数的8~15位
    pop eax
    pop edx

    push edx
    push eax
    mov al,ah
    mov dx,0x1f5
    out dx,al ;LBA参数的40~47位
    pop eax
    pop edx

    push edx
    push eax
    mov eax,edx
    shr eax,16
    mov dx,0x1f5
    out dx,al ;LBA参数的16~23位
    pop eax
    pop edx

    push edx
    push eax
    mov dx,0x1f6
    mov al,0100000b ;MasterDsk
    out dx,al
    pop eax
    pop edx

    push edx
    push eax
    mov dx,0x1f7
    mov al,0x24 ;ReadWrite
    out dx,al
    pop eax
    pop edx

    mov ebx,[.RevLBA48WriteregEbx]
    mov ecx,[.RevLBA48WriteregEcx]
    mov edx,[.RevLBA48WriteregEdx]
    mov eax,[.RevLBA48WriteregEax]


LBAwaitIdel:
    push dx
    push ax
    push cx
    mov dx,0x1f7
    out dx,al
    mov cx,0x07
    bt ax,cx
    jc LBAwaitIdel
    nop
    nop
    ret
    push cx
    pop ax
    pop dx