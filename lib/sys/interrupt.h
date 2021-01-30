/* Copyright (C) 2020 AlanCui
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
#pragma once
#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include <types.h>
struct intr_entry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t offset_high;
} __attribute__((__packed__));

struct intr_info
{
    addr_t *idt_addr;
};
//Base IDT Entry
extern struct intr_entry *sys_idt;
//INIT interrupt
extern void init_interrupt();
//Set an interrupt_gate
extern void set_intr_gate(uint32_t num,void * handle);
#endif