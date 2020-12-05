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
#include <mem.h>
#include <video.h>
#include <sysop.h>
//struct mem_info g_meminfo;
void init_mem(void)
{/*
    for (size_t i = 0; i < 48; i++) // 0-192MiB
    {
        *(((uint32_t*)(&sys_pdt_start)) + i) = ((uint32_t)(&sys_pt_start + 4096*i))<<12 + 0x0b;//Persent + Supervistor + Writethrouth + PCD
        for (size_t l = 0; l < 1024; l++)
        {
            *(&sys_pt_start + 1024*i + 4*1) = ((uint32_t)(l+i*4096))<<12 + 0x0b;//Persent + Supervistor + Writethrouth + PCD
        }
        
    }
    __asm__ ("movl $sys_pdt_start,%%eax\n\t"\
            "movl %%eax,%%cr3\n\t"\
    :::"memory") ;
    __asm__("movl %%cr0,%%eax\n\t"\
            "bts $31,%%eax\n\t"\
            "movl %%eax,%%cr0\n\t"\
        :::"memory");*/
}