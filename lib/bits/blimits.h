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
//Unsigned 16 bits
#define U16_MAX 0xffff
#define U16_MIN 0
//Signed 16 bits 
#define S16_MAX 0x7fff
#define S16_MIN -32768
//Unsigned 8 bits 
#define U8_MAX 256
#define U8_MIN 0
//Signed 8 bits
#define S8_MAX 127
#define S8_MIN -128
//Unsigned long
#define ULONG_MAX U32_MAX
#define ULONG_MIN U32_MIN
//Signed long
#define LONG_MAX S32_MAX
#define LONG_MIN S32_MIN
//Unsigned int
#define UINT_MAX ULONG_MAX
#define UINT_MIN ULONG_MIN
//Signed int
#define INT_MAX LONG_MAX
#define INT_MIN LONG_MIN
//Unsigned short
#define USHORT_MAX U16_MAX
#define USHORT_MIN U16_MIN
//Signed short
#define SHORT_MAX S16_MAX
#define SHORT_MIN S16_MIN
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