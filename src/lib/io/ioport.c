#include<gccm.h>
short in_port16(short port)
{
    short tmp = 0;
    __asm__ ASM_DNO ("inw %%dx,%%ax":"=a"(tmp):"d"(port):);
    return tmp;
}
short in_port8(short port)
{
    short tmp = 0;
    __asm__ ASM_DNO ("inb %%dx,%%al":"=a"(tmp):"d"(port):);
    return tmp;
}
void out_port16(short port,short valve)
{
    __asm__ ASM_DNO ("outw %%ax,%%dx"::"d"(port),"a"(valve):);
}
void out_port8(short port,char valve)
{
    __asm__ ASM_DNO ("outb %%al,%%dx"::"d"(port),"a"(valve):);
}