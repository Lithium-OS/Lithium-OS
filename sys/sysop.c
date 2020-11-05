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
#include <types.h>
uint64_t get_reg_rax()
{
    uint64_t tmp;
    __asm__ ASM_DNO("nop\n\t"
                    : "=a"(tmp)::);
    return tmp;
}
uint64_t get_reg_rbx()
{
    uint64_t tmp;
    __asm__ ASM_DNO("nop\n\t"
                    : "=b"(tmp)::);
    return tmp;
}

uint64_t get_reg_rcx()
{
    uint64_t tmp;
    __asm__ ASM_DNO("nop\n\t"
                    : "=c"(tmp)::);
    return tmp;
}

uint64_t get_reg_rdx()
{
    uint64_t tmp;
    __asm__ ASM_DNO("nop\n\t"
                    : "=d"(tmp)::);
    return tmp;
}
uint64_t get_reg_rsi()
{
    uint64_t tmp;
    __asm__ ASM_DNO("nop\n\t"
                    : "=S"(tmp)::);
    return tmp;
}
uint64_t get_reg_rdi()
{
    uint64_t tmp;
    __asm__ ASM_DNO("nop\n\t"
                    : "=D"(tmp)::);
    return tmp;
}
void set_reg_rax(uint64_t tmp)
{
    __asm__ ASM_DNO("nop\n\t"
                    ::"a"(tmp):);
}
void set_reg_rbx(uint64_t tmp)
{

    __asm__ ASM_DNO("nop\n\t"
                    ::"b"(tmp):);

}

void set_reg_rcx(uint64_t tmp)
{

    __asm__ ASM_DNO("nop\n\t"
                    ::"c"(tmp):);

}

void set_reg_rdx(uint64_t tmp)
{

    __asm__ ASM_DNO("nop\n\t"
                    ::"d"(tmp):);

}
void set_reg_rsi(uint64_t tmp)
{

    __asm__ ASM_DNO("nop\n\t"
                    ::"S"(tmp):);

}
void set_reg_rdi(uint64_t tmp)
{

    __asm__ ASM_DNO("nop\n\t"
                    ::"D"(tmp):);

}
void hlt_cpu(void)
{
    __asm__ ASM_DNO("hlt\n\t" ::
                        : "memory");
}
