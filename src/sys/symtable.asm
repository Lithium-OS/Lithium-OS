org 0x7e00
SYM_SECT:                               ;7e00
dw 0xff
SYM_LBA48_ASM_WORD_PER_SECTOR:          ;7e02
dw 32
SYM_DISK_ASM_DAP_CACHE:
    SYM_DISK_ASM_DAP_CACHE_SIZE:
db 0xff                                 ;7e04
    SYM_DISK_ASM_DAP_CACHE_REV:
db 0xff                                 ;7e05
    SYM_DISK_ASM_DAP_CACHE_COUNT:
dw 0xffff                               ;7e06
    SYM_DISK_ASM_DAP_CACHE_TARGET:
dd 0xffffffff                           ;7e08
    SYM_DISK_ASM_DAP_CACHE_STARTS:
dq 0xffffffffffffffff                   ;7e0c
times 984-($$-$) db 0x00