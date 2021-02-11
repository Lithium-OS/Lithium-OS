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
extern uint32_t syscall_cls;
extern void *syscall_ptr;
extern uint8_t * kbb_p;
extern uint32_t g_kmaincnt;
extern void _do_irq33(void);
extern void _do_irq13(void);
extern void _do_irq14(void);
extern void _do_irq80(void);
extern void _do_irq3(void);
extern void _do_irq0(void);
extern void _do_irq4(void);
extern void _do_irq5(void);
extern void _do_irq6(void);
extern void _do_irq7(void);
extern void _do_irq8(void);
extern void _do_irq9(void);
extern void _do_irq10(void);
extern void _do_irq11(void);
extern void _do_irq12(void);
extern void _do_irq13(void);
extern void _do_irq14(void);
extern void _do_irq15(void);
extern void _do_irq16(void);
extern void _do_irq17(void);
extern void _do_irq18(void);
extern void _do_irq19(void);
extern void _do_irq20(void);
extern void _do_irq21(void);
extern void _do_irqnull(void);
extern void _do_irq32(void);
struct intr_info g_sysintr;
uint32_t cnt = 0;
void do_irq32(void)
{
    g_kmaincnt++;
}
void do_irq33(void)
{
    klog("imgr","get int 33");
    if (*kbb_p != 0xff)//bufEND
    {
            *kbb_p = in_port8(0x60);
        kbb_p--;
        out_port8(0x20,0x20);
    }
}
void do_irq3(uint32_t edx,uint32_t ecx,uint32_t ebx,uint32_t eax)
{
    klog("imgr","int 3 : debug intrrupt");
    hlt_cpu();
}
void do_irq80(void)
{
    //TODO wwww
}
void do_irq0(void)
{
    panic("Divide Error");
    return;
}
void do_irq4(void)
{
    panic("Overflow");
    return;
}
void do_irq5(void)
{
    panic("BOUND Range Exceeded");
    return;
}
void do_irq6(void)
{
    panic("Invalid Opcode (Undefined Opcode)");
    return;
}
void do_irq7(void)
{
    panic("Device Not Available (No Math Coprocessor)");
    return;
}
void do_irq8(void)
{
    panic("Double Fault");
    return;
}
void do_irq9(void)
{
    panic("CoProcessor Segment Overrun (reserved");
    return;
}
void do_irq10(void)
{
    panic("Invalid TSS");
    return;
}
void do_irq11(void)
{
    panic("Segment Not Present");
    return;
}
void do_irq12(void)
{
    panic("Stack Segment Fault");
    return;
}
void do_irq13(void)
{
    kputstr(0,7,"GP General Protection Error",RED,WHITE);
    return;
}
void do_irq14(void)
{
    kputstr(0,7,"PF Page Fault              ",RED,WHITE);
    return;
}
void do_irq16(void)
{
    panic("Floating-Point Error (Math Fault)");
    return;
}
void do_irq17(void)
{
    panic("Alignment Check");
    return;
}
void do_irq18(void)
{
    panic("Machine Check");
    return;
}
void do_irq19(void)
{
    panic("SIMD Floating-Point Exception");
    return;
}
void do_irq20(void)
{
    panic("Virtualization Exception");
    return;
}
void do_irq21(void)
{
    panic(" Control Protection Exception");
    return;
}
void do_irqnull(void)
{
    panic("UKE Unknow Error or Fault  ");
    return;
}
void init_interrupt()
{
    klog("imgr","init idt");
    g_sysintr.idt_addr = &sys_idt;
    set_intr_gate(33,&_do_irq33);
    set_intr_gate(13,&_do_irq13);
    set_intr_gate(14,&_do_irq14);
    klog("imgr","init intr_gate 80 -> _do_irq_80(Syscall)");
    set_intr_gate(80,&_do_irq80);
    set_intr_gate(3,&_do_irq3);
    set_intr_gate(4,&_do_irq4);
    set_intr_gate(5,&_do_irq5);
    set_intr_gate(6,&_do_irq6);
    set_intr_gate(7,&_do_irq7);
    set_intr_gate(8,&_do_irq8);
    set_intr_gate(9,&_do_irq9);
    set_intr_gate(10,&_do_irq10);
    set_intr_gate(11,&_do_irq11);
    set_intr_gate(12,&_do_irq12);
    set_intr_gate(13,&_do_irq13);
    set_intr_gate(14,&_do_irq14);
    set_intr_gate(16,&_do_irq16);
    set_intr_gate(17,&_do_irq17);
    set_intr_gate(18,&_do_irq18);
    set_intr_gate(19,&_do_irq19);
    set_intr_gate(20,&_do_irq20);
    set_intr_gate(21,&_do_irq21);
    set_intr_gate(32,&_do_irq32);

    //klog("imgr","init intr_gate 16 -> do_irq_16(PIT)");
   // set_intr_gate(16,&_do_irq16);
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