 ;   Copyright (C) 2020 LithiumOS-Team

 ;   This program is free software: you can redistribute it and/or modify
 ;   it under the terms of the GNU Affero General Public License as
 ;   published by the Free Software Foundation, either version 3 of the
 ;   License, or (at your option) any later version.
 ;
 ;   This program is distributed in the hope that it will be useful,
 ;   but WITHOUT ANY WARRANTY; without even the implied warranty of
 ;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ;   GNU Affero General Public License for more details.

 ;  You should have received a copy of the GNU Affero General Public License
 ;  along with this program.  If not, see <https://www.gnu.org/licenses/>.

;===写死的文件长度,注意更改!
org 0x7c6a

mov ax,0x0600
mov bx,0x0700
mov cx,0x00
mov dx,0x184f
int 0x10

mov ax,0x00
mov ds,ax
mov ax,DskPack
mov si,ax
mov dl,0x80
mov ah,0x42
int 0x13
jc Fail
jnc Succ
Fail:
    mov cx,25
    mov dh,0x00
    mov dl,0x00
    mov bx,Failmsg
    call ShowMessage
    jmp $
Succ:
    mov cx,28
    mov dh,0x01
    mov dl,0x00
    mov bx,Succmsg
    call ShowMessage
    jmp 0x0000:0x7e00
    jmp $
DskPack:
db 0x10
db 0x00
dw 4
dw 0x7e00
dw 0x0000
dq 4128
; cx: length, dh: row, dl: col, bx: string addr
ShowMessage:
    mov ax, ds
    mov es, ax
    mov bp, bx
    mov ax, 0x1301
    mov bx, 0x000f
    int 0x10
    ret
Failmsg:
    db "[Boot]Cannot Read Loader."
Succmsg:
    db "[Boot]Found Loader,Jumping."
times 238 db 0x00
dw 0xaa55