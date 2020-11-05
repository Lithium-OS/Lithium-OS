OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_kstart)
SECTIONS
{
    . = 32M;
    .text ALIGN(8):
    {
        *(.mbt2std)
        *(.text)
    }
    .rodata :
    {
        *(.data)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
}