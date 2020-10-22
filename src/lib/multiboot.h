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
#include <gccm.h>
#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_
#define MBT_VERSION 2
#if MBT_VERSION==2

#define MBT_END_TYPE 0
#define MBT_VBUF_TYPE 5
#define MBT_ELF64_TYPE 9
#define MBT_RELOCT_TYPE 10

#define MBT_LDPHT_ADDR 0x200000
#define MBT_LDR_MAGIC 0xe85250d6
#define MBT_ARCH_i386 0

/*Needs To Config*/
#define MBT_NOW_ARCH 0
/*****************/
#if 0
struct mbt_header
{
    const long magic;
    const long arch;
    const long h_len;
    const long h_chksum;
};

struct mbt_elf_64
{
    const short type;
    short flags;
    const long size;
};
struct mbt_vbuf
{
    const short type;
    short flags;
    const long size;
    long width;
    long height;
    long depth;
};
struct mbt_reloct
{
    const short type;
    short flags;
    const long size;
    long min_addr;
    long max_addr;
    long align;
    long perf;
};
struct mbt_endtag
{
    const short type;
    const short flags;
    const long size;
};
#endif
#else 
#error NOT SUPPORT MBT_VERSION
#endif
#endif