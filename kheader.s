.section .mbt2std
tag_start:
.long 0xE85250D6
.long 0
.long tag_end-tag_start
.long -1*(tag_end-tag_start + 0 +  0xE85250D6)

.vbe:
.short 5
.short 0
.long 20
.long 1024
.long 768
.long 32
.vbe_e:
.long 0
#.efi:
#.short 9
#.short 0
#.long 12
#.long 0x1000000
#.efi_e:
#.long 0
#.short 0
#.short 0
#.long 8
tag_end:
.long 0xffffffffffffffff
_kstart:
    movl $0x114514,%eax
    hlt
.globl _kstart
