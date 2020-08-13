;ax 存扇区数 ebx 存开始扇区编号 ecx 段地址:偏移地址
LBAReadSector:
    mov [SYM_DISK_ASM_DAP_CACHE_COUNT],ax
    mov [SYM_DISK_ASM_DAP_CACHE_STARTS],ebx
    mov [SYM_DISK_ASM_DAP_CACHE_TARGET],ecx
    mov ah,0x42
    mov dl,0x80
    mov si,SYM_DISK_ASM_DAP_CACHE
