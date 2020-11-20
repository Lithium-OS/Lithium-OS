ENTRY(_kstart)
SECTIONS
{
    . = 1M;
    .intpg1M ALIGN(4K):
    {
        *(.intpg1M)
    }
    . = 2M;
    .intpg2M ALIGN(4K):
    {
        *(.intpg2M)
    }
    . = 32M;
    .text ALIGN(8):
    {
        *(.mbt2std)
        *(.text)
    }
    .rodata :
    {
        *(.rodata)
    }
    .bss :
    {
        *(.bss)
    }
}