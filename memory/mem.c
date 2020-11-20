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
uint8_t g_lsmemmag[128]={0};
struct mem_info g_meminfo;
void init_mem(void)
{
    kputstr(0,10,"Init Memory",WHITE,BLACK);
    g_meminfo.mgn = g_lsmemmag;
    for (size_t i = 0; i < 64; i++)
    {
        g_meminfo.mgn[i] = 0xff; // 0-128MiB Used (Kernel)
    }
    kputstr(0,11,"Memory 0 - 128 MiB Used (Kernel File)",WHITE,BLACK);
    for (size_t i = 64; i < 80; i++)
    {
        g_meminfo.mgn[i] = 0xff; // 128-160MiB Used (Kernel Stack)
    }
    kputstr(0,12,"Memory 128 - 160 MiB Used (Kernel Stack)",WHITE,BLACK);
    kputstr(0,13,"ebp->0xa000000 (160Mib) (Kernel Stack)",WHITE,BLACK);
}