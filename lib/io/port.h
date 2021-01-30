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
#ifndef _IOPORT_H_
#define _IOPORT_H_
#include <types.h>
__attribute__((always_inline)) inline static uint16_t in_port16(uint16_t port)
{
    uint16_t tmp = 0;
    __asm__ __volatile__("inw %%dx,%%ax"
                         : "=a"(tmp)
                         : "d"(port)
                         :);
    return tmp;
}
__attribute__((always_inline)) inline static uint8_t in_port8(uint16_t port)
{
    uint8_t tmp = 0;
    __asm__ __volatile__("inb %%dx,%%al"
                         : "=a"(tmp)
                         : "d"(port)
                         :);
    return tmp;
}
__attribute__((always_inline)) inline static void out_port16(uint16_t port, uint16_t valve)
{
    __asm__ __volatile__("outw %%ax,%%dx" ::"d"(port), "a"(valve)
                         :);
}
__attribute__((always_inline)) inline static void out_port8(uint16_t port, uint8_t valve)
{
    __asm__ __volatile__("outb %%al,%%dx" ::"d"(port), "a"(valve)
                         :);
}
#endif