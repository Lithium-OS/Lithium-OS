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
#ifndef _BLIMITS_H_
#define _BLIMITS_H_
//Unsigned 32 bits
#define U32_MAX 0xffffffff
#define U32_MIN 0
//Signed 32 bits
#define S32_MAX 0x7fffffff
#define S32_MIN -2147483648
//Unsigned long
#define ULONG_MAX U32_MAX
#define ULONG_MIN U32_MIN
//Signed long
#define SLONG_MAX S32_MAX
#define SLONG_MIN S32_MIN
//Size_t
#ifdef __i386__
#define SIZE_T_MAX ULONG_MAX 
#define SIZE_T_MIN ULONG_MIN
#endif
#ifdef __amd64
//#error ULONGLONG is not defined
#define SIZE_T_MAX ULONG_MAX
#endif
#endif