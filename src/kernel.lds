OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(kmain)
SECTIONS
{
    . = 0x200000;
    .osstart :
    {
        *(.osstart)
    }
    .mbt2std : 
    {
        *(.mbt2std)
    }
    .text :
    {
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