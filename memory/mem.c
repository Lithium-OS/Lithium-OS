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
#include <errno.h>
#include <mm/mem.h>
#include <console/tty.h>
#include <sys/sysop.h>
#include <console/video.h>
#include <io/port.h>
#define set_pt(a, b, c) set_pdt(a, b, c)

void set_pdt(void *dst, void *pt, uint16_t flag)
{
    *(uint32_t *)dst = (((uint32_t)pt & 0xfffff000) | (flag & 0xfff));
}
//struct mem_info g_meminfo;
char ctrlp_lst[30000] = {0};
size_t g_to4kpgs = 0;
uint32_t errno = 0;
void init_mem(void)
{
    // klog("mmc","system memory aera:");
    // klog("mmc","---sys_fp_start: %h (linear)",&sys_fp_start);
    klog("mmc", "init kernel base 4-Kib aera");
    klog("mmc", "total available: %h bytes", &sys_fp_end - &sys_fp_start);
    klog("mmc", "             ");
    g_to4kpgs = (&sys_fp_end - &sys_fp_start) / 4096;
    klog("mmc", "total available : %h page(s)", (&sys_fp_end - &sys_fp_start) / 4096);
    klog("mmc", "             ");
    klog("mmc", "4-kib aera ok");
    /*
    for (size_t i = 0; i < INIT_PAGE_MIB * 1024 * 1024 / 4096 / 1024 ; i++)
    {
        set_pdt((char *)&sys_pdt_start+i,(char *)&sys_pt_start+i*1024,3);
        for (size_t n = 0; n < 1024; n++)
            set_pdt((int*)((char *)&sys_pt_start+i*1024)+n,(int*)(i*1024*4096+n*4096) ,3);
    }
    for (size_t i = g_sysgrap.base_addr / 4096 / 1024 ; i < (g_sysgrap.base_addr / 1024 +3)/ 4096 ; i++)
    {
        set_pdt((char *)&sys_pdt_start+i,(char *)&sys_pt_start+i*1024,3);
        for (size_t n = 0; n < 1024; n++)
            set_pdt((int*)((char *)&sys_pt_start+i*1024)+n,(int*)(i*1024*4096+n*4096) ,3);
    }
        klog("MMC","ok!");
    __asm__ ("movl $sys_pdt_start,%%eax\n\t"\
            "movl %%eax,%%cr3\n\t"\
    :::"memory") ;
    __asm__("movl %%cr0,%%eax\n\t"\
            "or $0x80000001,%%eax\n\t"\
            "movl %%eax,%%cr0\n\t"\
        :::"memory");
    hlt_cpu();
    out_port16(0x3f8,'N');
    out_port16(0x3f8,'M');  
    out_port16(0x3f8,'S');
    out_port16(0x3f8,'L');
    */

}
void *kpmalloc(size_t n)
{
    for (size_t i = 0; i < g_to4kpgs; i++)
        if (ctrlp_lst[i] == PAGE_FREE)
            for (size_t j = 0; j < n; i++)
                if(ctrlp_lst[i+j] == PAGE_DIRTY)
                    break;
                else
                {
                    ctrlp_lst[i+j] = PAGE_DIRTY;
                    return i*4096+&sys_fp_start;
                }
    klog("mmc", "kernel all page(s) are alloced:%h                   ", g_to4kpgs);
    return -ENOMEM;
}
void kpfree(void *ptr)
{
    ctrlp_lst[(int)((char *)ptr - sys_fp_start) / 4096] = PAGE_DIRTY;
    return;
}