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
#include "../lib/stdint.h"
#ifndef _PROC_H_
#define _PROC_H_
typedef struct proc_des
{
    volatile uint16_t stat;
    uint16_t flags;
    uint16_t pid;
    uint32_t base_mem;
    uint32_t len_mem;
    volatile uint32_t cnt_time;
    volatile uint32_t sig;
    volatile uint32_t pri;

    proc_mdes mem;
    proc_tss tss;
}proc_des;
typedef struct proc_mdes
{
    uint32_t mem_cstart,mem_cend;
    uint32_t mem_dstart,mem_dend;
    uint32_t mem_rodstart,mem_rodend;
    uint32_t mem_heapstart,mem_heapend;
    uint32_t mem_stack;
}proc_mdes;
typedef struct proc_tss
{
    volatile uint32_t eax,ebx,ecx,edx,eip,esi,edi,esp,ebp,eflags;
    volatile uint16_t cs,ds,ss,es,fs,gs;
    volatile uint32_t trap,err_code;
}proc_tss;


#endif