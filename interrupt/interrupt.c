/*
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
/*Copyright (C) 2020-2021 AlanCui*/
#include <types.h>
#include <io/port.h>
#include <sys/interrupt.h>
#include <sys/sysop.h>
#include <console/video.h>
extern uint8_t * kbb_p;
extern void _do_irq33(void);
extern void _do_irq13(void);
extern void _do_irq14(void);
extern void _do_irqnull(void);
struct intr_info g_sysintr;
uint32_t cnt = 0;
void do_irq33(void)
{
    klog("imgr","get int 33");
    if (*kbb_p != 0xff)//bufEND
    {
            *kbb_p = in_port8(0x60);
        kbb_p--;
        out_port8(0x20,0x20);
        return;
    }
}
void do_irq13(void)
{
    kputwstr(0,7,L"#GP General Protection Error",RED,WHITE);
    return;
}
void do_irq14(void)
{
    kputwstr(0,7,L"#PF Page Fault              ",RED,WHITE);
    return;
}
void do_irqnull(void)
{
    kputwstr(0,7,L"#UKE Unknow Error or Fault  ",RED,WHITE);
    return;
}
void init_interrupt()
{
    klog("imgr","init idt");
    g_sysintr.idt_addr = &sys_idt;
    klog("imgr","init intr_gate 0-32 -> null");
    
    for (size_t i = 0; i < 32; i++)
    {
        set_intr_gate(i,&_do_irqnull);
    }
    klog("imgr","init intr_gate 33 -> _do_irq_33(Keyboard Driver)");
    set_intr_gate(33,&_do_irq33);
    klog("imgr","init intr_gate 13 -> _do_irq_13(#GP General Protection Error)");
    set_intr_gate(13,&_do_irq13);
    klog("imgr","init intr_gate 14 -> _do_irq_14(#PF Page Fault)");
    set_intr_gate(14,&_do_irq14);

    klog("imgr","init kb_master_contorller");
    out_port8(0x20,0x11);
    out_port8(0x21,0x20);
    out_port8(0x21,0x04);
    out_port8(0x21,0x01);

    klog("imgr","init kb_slave_contorller");
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