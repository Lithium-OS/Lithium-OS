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
BPB_HiddSec         dd 00 
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

    mov ah,0x42
    mov si,ReadSymPacket
    int 0x13            ;读符号表
    jc Fail

ReadSymPacket:
db 0x10 ;32bit wide
db 0x00 ;Rev
dw 0x01 ;1 Sector
dd 0x7e00 ;Address
dq 0x02 ;No.3 Sector

    mov ax,64
    mov ebx,4128
    mov ecx,0x8200
    call LBAReadSector
    jc Fail
    jmp 0x8200

Fail:
    mov bx, MsgFail
    mov cx, 19
    mov dx, 0x0100
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

%include "../inc/bootstage/realmode/disk.asm"

MsgFail db "[boot] Boot failed."

;times 346 db 0x00
times 301 db 0

dw 0xaa55