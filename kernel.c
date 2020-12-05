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
#include <tty.h>
#include <interrupt.h>
#include <mem.h>
#include <keyboard.h>
extern uint32_t fb_addr;
extern uint32_t mem_info;
extern char logo_cpu[];
int kmain()
{
    __asm__("movl $0xa000000,%eax");
    __asm__("movl %eax,%ebp");
    __asm__("movl %eax,%esp");
    g_sysgrap.base_addr = fb_addr;
    g_sysgrap.res_x = 1024;
    g_sysgrap.res_y = 768;
    kputstr(0, 0, "Welcome to Lithium OS!!          (2020_11_21_A02)", WHITE, BLACK);
    kputstrc(0, 1,logo_cpu, GREEN, BLACK, 52);
    kputstr(0,2,"Ready",GREEN,BLACK);
    init_interrupt();
    //out_port8(0x21,0xff);//BACU
    init_mem();
    char wdnmd[512] = {0};
    ata_read_sector(ata_port_master,1,wdnmd);
    for (size_t i = 0; i < 16; i++)
    {
        kputnum(20,5+i,*(((uint32_t *)wdnmd)+i),YELLOW,BLACK);
    }
    
    while (1)
    {
        als_keyborad_code();
    }
}
