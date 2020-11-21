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
#include <multiboot.h>
#include <types.h>
#include <ioport.h>
#include <sysop.h>
#include <video.h>
#include <ata.h>
extern uint8_t logo_cpu[];
int kmain()
{
    __asm__("movl $0xa000000,%eax");
    __asm__("movl %eax,%ebp");
    __asm__("movl %eax,%esp");
    g_sysgrap.base_addr = get_reg_edx();
    g_sysgrap.res_x = 1024;
    g_sysgrap.res_y = 768;
    kputstr(0, 0, "Welcome to Lithium OS!!", WHITE, BLACK);
    kputchar(34,0,'A',GREEN,BLACK);
    kputchar(36,0,'A',GREEN,BLACK);
    kputchar(37,0,'A',GREEN,BLACK);
    kputwchar(35,0,'A',BLUE,BLACK);
    kputstr(0, 1, "EAX:", WHITE, BLACK);
    kputnum(4, 1, get_reg_eax(), WHITE, BLACK);
    kputstr(0, 2, "EBX:", WHITE, BLACK);
    kputnum(4, 2, get_reg_ebx(), WHITE, BLACK);
    kputstr(0, 3, "ECX:", WHITE, BLACK);
    kputnum(4, 3, get_reg_ecx(), WHITE, BLACK);
    kputstr(0, 4, "EDX:", WHITE, BLACK);
    kputnum(4, 4, get_reg_edx(), WHITE, BLACK);
    kputstr(0, 5, "ESI:", WHITE, BLACK);
    kputnum(4, 5, get_reg_esi(), WHITE, BLACK);
    kputstr(0, 6, "EDI:", WHITE, BLACK);
    kputnum(4, 6, get_reg_edi(), WHITE, BLACK);
    kputstr(0, 7, "VGA:           @             x             TEXT:             x            ", WHITE, BLACK);
    kputnum(4, 7, g_sysgrap.base_addr, WHITE, BLACK);
    kputnum(17, 7, g_sysgrap.res_x, WHITE, BLACK);
    kputnum(32, 7, g_sysgrap.res_y, WHITE, BLACK);
    kputnum(49, 7, g_sysgrap.res_x / 8, WHITE, BLACK);
    kputnum(63, 7, g_sysgrap.res_y / 16, WHITE, BLACK);
    kputchar(0, 8, '0', RED, BLACK);
    kputchar(1, 8, '0', GREEN, BLACK);
    kputchar(2, 8, '0', BLUE, BLACK);
    kputchar(3, 8, '0', YELLOW, BLACK);
    kputchar(4, 8, '0', CYAN, BLACK);
    kputchar(5, 8, '0', PINK, BLACK);
    init_interrupt();
    //out_port8(0x21,0xff);//BACU
    init_mem();
    kputstrc(0, 9, logo_cpu, GREEN, BLACK, 52);

    while (1)
    {
        als_keyborad_code();
    }
}
