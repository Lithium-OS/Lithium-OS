/* Copyright (C) 2020-2021 AlanCui
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
#ifndef _SYSOP_H_
#define _SYSOP_H_
#include <types.h>
#ifdef __cplusplus
extern "C"
{
#endif
__attribute__((always_inline)) inline static regv_t get_reg_eax()
{
    regv_t __tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=a"(__tmp)::);
    return __tmp;
}
__attribute__((always_inline)) inline static regv_t get_reg_ebx()
{
    regv_t __tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=b"(__tmp)::);
    return __tmp;
}

__attribute__((always_inline)) inline static regv_t get_reg_ecx()
{
    regv_t __tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=c"(__tmp)::);
    return __tmp;
}

__attribute__((always_inline)) inline static regv_t get_reg_edx()
{
    regv_t __tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=d"(__tmp)::);
    return __tmp;
}
__attribute__((always_inline)) inline static regv_t get_reg_esi()
{
    regv_t __tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=S"(__tmp)::);
    return __tmp;
}
__attribute__((always_inline)) inline static regv_t get_reg_edi()
{
    regv_t __tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=D"(__tmp)::);
    return __tmp;
}
__attribute__((always_inline)) inline static uint16_t get_reg_cs()
{
    uint16_t __tmp;
    __asm__ __volatile__("movw %%cs,%%ax\n\t"
                         : "=a"(__tmp)::);
    return __tmp;
}
__attribute__((always_inline)) inline static void hlt_cpu(void)
{
    __asm__ __volatile__("hlt\n\t" ::
                             : "memory");
}
__attribute__((always_inline)) inline static void sti(void)
{
    __asm__ __volatile__("sti\n\t" ::
                             : "memory");
}
#ifdef __cplusplus
}
#endif
#endif