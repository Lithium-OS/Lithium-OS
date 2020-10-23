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
#include <sys/types.h>
#ifndef _SYSOP_H_
#define _SYSOP_H_
//Get the valve of RAX
extern uint64_t get_reg_rax();
//Get the valve of RBX
extern uint64_t get_reg_rbx();
//Get the valve of RCX
extern uint64_t get_reg_rcx();
//Get the valve of RDX
extern uint64_t get_reg_rdx();
//Get the valve of RSI
extern uint64_t get_reg_rsi();
//Get the valve of RDI
extern uint64_t get_reg_rdi();
//Halt Cpu
extern void hlt_cpu();
#endif