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
    . = 128M;
    sys_pdt_start = .;
    .pdt ALIGN(4K):
    {
        *(.pdt)
    }
    . = 130M;
    sys_pt_start = .;
    .pt ALIGN(4K):
    {
        *(.pt)
    }
    . = 142M;
    sys_fp_start = .;
    . = 256M;
    sys_fp_end = .;

}