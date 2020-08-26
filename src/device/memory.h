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
/*MainDevloper: AlanCui*/
#include "../lib/stdint.h"
typedef struct mem_table
{
    uint64_t base;
    uint64_t len;
    uint32_t attr;
    uint32_t rev;
}mem_table;
typedef struct mem_pagedes
{
    uint32_t addr;
    uint16_t pid;
    uint8_t attr;
    /*0000CKBG*/
    /*G - Global        */
    /*B - Busy          */
    /*K - Kernel/User   */
    /*C - Clean         */
    uint32_t len_ptr;
    /*Head:num*/
    /*Not Head  0x0fffffff*/
}mem_pagedes; 

typedef struct mem_b_ll
{
    mem_b_ll* next_ll;
    uint16_t ptr;
    uint16_t end;
}mem_b_ll;
