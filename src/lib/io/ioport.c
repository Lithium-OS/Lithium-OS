 /* Copyright (C) 2020 LithiumOS-Team
    This file is part of the Lithium Kernel.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include<gccm.h>
short in_port16(short port)
{
    short tmp = 0;
    __asm__ ASM_DNO ("inw %%dx,%%ax":"=a"(tmp):"d"(port):);
    return tmp;
}
char in_port8(short port)
{
    char tmp = 0;
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