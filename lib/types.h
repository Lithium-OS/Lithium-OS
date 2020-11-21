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
#pragma once
#ifndef _TYPE_H_
#define _TYPE_H_
//8-bit unsigned integer type
typedef unsigned char uint8_t;
//16-bit unsigned integer type
typedef unsigned short uint16_t;
//32-bit unsigned integer type
typedef unsigned long uint32_t;
//64-bit unsigned integer type
typedef unsigned long long uint64_t;
//typedef void* addr_t;
#ifdef __i386__
//32-bit unsigned integer type(i386)
typedef uint32_t size_t;
#endif
#ifdef __amd64
//64-bit unsigned integer type(amd64)
typedef uint64_t size_t;
#endif
//Address TypeF
typedef void addr_t;
#ifdef __i386__
//32-bit address integer type(i386)
typedef uint32_t addri_t;
#endif
#ifdef __amd64
//64-bit address integer type(amd64)
typedef uint64_t addri_t;
#endif
//8-bit unsigned integer type
typedef signed char sint8_t;
//8-bit unsigned integer type
typedef signed short sint16_t;
//8-bit unsigned integer type
typedef signed long sint32_t;
//8-bit unsigned integer type
typedef signed long long sint64_t;
#ifdef __i386__
//32-bit unsigned integer type(i386)
typedef uint32_t regv_t;
#endif
#ifdef __amd64
//64-bit unsigned integer type(amd64)
typedef uint64_t regv_t;
#endif
#define NULL (void *)0
typedef uint32_t wchar_t;
#endif