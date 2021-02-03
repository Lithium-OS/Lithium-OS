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
#pragma once
#ifndef _MEM_H_
#define _MEM_H_

#define INIT_PAGE_MIB 256

#include <types.h>
struct mem_info
{
    uint8_t *mgn;
};

#ifdef __cplusplus
extern "C"
{
#endif

#include "../memory/slab.h"

extern void init_mem(void);
extern void *kpmalloc(size_t n);
extern uint32_t sys_pdt_start;
extern uint32_t sys_pt_start;
extern char sys_fp_start;
extern char sys_fp_end;


#define PAGE_FREE 0
#define PAGE_DIRTY 1
#define PAGE_BUSY 2
#define PAGE_BROKEN 3

#ifdef __cplusplus
}
#endif
#endif 