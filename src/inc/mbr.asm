;栈传参,压入:目的地址
ReadDiskMBR:
    .ReadDiskMBReax:
        dd 0x00
    mov [.ReadDiskMBReax],eax
    pop eax
    push WORD 0x00 ;第1扇区
    push DWORD 0x01
    push WORD 0x01 ;1个扇区
    push DWORD eax ;存到eax地址