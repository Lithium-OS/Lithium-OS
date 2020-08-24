#include "../lib/type.h"
int out_port16(uint16_t portname,uint16_t valve)
{
    __asm__ __volatile__("outw %0,%1"::"r"(portname),"r"(valve));
    return 0;
}
int out_port8(uint16_t portname,uint16_t valve)
{
    __asm__ __volatile__("outb %0,%1"::"r"(portname),"r"(valve));
    return 0;
}
uint16_t in_port16(uint16_t portname)
{
    uint16_t opt;
    __asm__ __volatile__("inw %1,%0":"=r"(opt):"r"(portname));
    return opt;
}
uint8_t in_port8(uint16_t portname)
{
    uint8_t opt;
    __asm__ __volatile__("inb %1,%0":"=r"(opt):"r"(portname));
    return opt;
}