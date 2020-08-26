 /* Copyright (C) 2020 LithiumOS-Team

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
/*MainDevloper: AlanCui*/
#include "../lib/stdint.h"
uint16_t out_port16(uint16_t portname,uint16_t valve)
{
    __asm__ __volatile__("outw %0,%1"::"r"(portname),"r"(valve));
    return 0;
}
uint16_t out_port8(uint16_t portname,uint8_t valve)
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