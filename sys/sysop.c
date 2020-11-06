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
regv_t get_reg_rax()
{
    regv_t tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=a"(tmp)::);
    return tmp;
}
regv_t get_reg_rbx()
{
    regv_t tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=b"(tmp)::);
    return tmp;
}

regv_t get_reg_rcx()
{
    regv_t tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=c"(tmp)::);
    return tmp;
}

regv_t get_reg_rdx()
{
    regv_t tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=d"(tmp)::);
    return tmp;
}
regv_t get_reg_rsi()
{
    regv_t tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=S"(tmp)::);
    return tmp;
}
regv_t get_reg_rdi()
{
    regv_t tmp;
    __asm__ __volatile__("nop\n\t"
                         : "=D"(tmp)::);
    return tmp;
}
void hlt_cpu(void)
{
    __asm__ __volatile__("hlt\n\t" ::
                             : "memory");
}
