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
#include <types.h>
#include <ioport.h>
#include <interrupt.h>
#include <sysop.h>
#include <video.h>
extern uint8_t * kbb_p;
extern void _do_irq33(void);
struct intr_info g_sysintr;
uint32_t cnt = 0;
void do_irq33(void)
{
    if (*kbb_p != 0xff)//bufEND
    {
            *kbb_p = in_port8(0x60);
        kbb_p--;
        out_port8(0x20,0x20);
        return;
    }
}

void init_interrupt()
{
    kputstr(0,9,"Init Interrupt",WHITE,BLACK);
    g_sysintr.idt_addr = &sys_idt;
    set_intr_gate(33,&_do_irq33);

    
    out_port8(0x20,0x11);
    out_port8(0x21,0x20);
    out_port8(0x21,0x04);
    out_port8(0x21,0x01);

    out_port8(0xa0,0x11);
    out_port8(0xa1,0x28);
    out_port8(0xa1,0x02);
    out_port8(0xa1,0x01);

    out_port8(0x21,0xfd);
    out_port8(0xa1,0xff);

    __asm__ ("sti");
}
void set_intr_gate(uint32_t num,void * handle)
{
    addr_t * tmp =g_sysintr.idt_addr + num * 8;
    ((struct intr_entry *)tmp)->offset_low = (uint16_t)((regv_t)handle & 0xffff);
    ((struct intr_entry *)tmp)->offset_high = (uint16_t)((regv_t)handle >> 16);
    ((struct intr_entry *)tmp)->selector = get_reg_cs();
    ((struct intr_entry *)tmp)->type = 0x8e; // r 
}