;===写死的文件长度,注意更改!
org 0x7c00

nop
jmp StartBoot

BS_OEMName          db "MSDOS5.0"
BPB_BytesPerSec     dw 512
BPB_SecPerClus      db 8
BPB_RavdSecCnt      dw 36
BPB_NumFATs         db 2
BPB_RootEntCnt      dw 0x00
BPB_TotSec16        dw 0x00 
BPB_Media           db 0xf8 ;硬盘
BPB_FATSz16         dw 0x00
BPB_SecPerTrk       dw 63
BPB_NumHeads        dw 255
BPB_HiddSec         dd 36 
BPB_TotSec32        dd 2095104
BPB_FATSz32         dd 2042
BPB_ExtImage        dw 0x00
BPB_FSVer           dw 0x00
BPB_RootClus        dd 0x02
BPB_FSInfo          dw 0x01
BPB_BkBootSec       dw 0x06
BPB_Reserved        dq 0x00
                    dd 0x00
BS_DrvNum           db 0x80
BS_Reservedl        db 0x00
BS_BootSig          db 0x29
BS_VolID            dd 0x00114514
BS_VolLab           db "SystemDisk"
                    db 0x00
BS_FileSysType      db "FAT32   "
StartBoot:

times 420 db 0x00

dw 0xaa55