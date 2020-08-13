;ax 存扇区数 ebx 存开始扇区编号 ecx 段地址:偏移地址
LBAReadSector:
    mov [0x7e06],ax
    mov [0x7e0c],ebx
    mov [0x7e08],ecx
    mov ah,0x42
    mov dl,0x80
    mov si,0x7e04
