//
// vadefs.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Definitions of macro helpers used by <stdarg.h>.  This is the topmost header
// in the CRT header lattice, and is always the first CRT header to be included,
// explicitly or implicitly.  Therefore, this header also has several definitions
// that are used throughout the CRT.
//
#pragma once
#define _INC_VADEFS

#define _CRT_PACKING 8
#pragma pack(push, _CRT_PACKING)
typedef unsigned int uintptr_t;
typedef char* va_list;
#define _ADDRESSOF(v) (&(v))
#define _SLOTSIZEOF(t)  (sizeof(t))
#define _APALIGN(t,ap)  (__alignof(t))
    #define _INTSIZEOF(n)          ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
    #define va_start_a(ap, v) ((void)(ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v)))
    #define va_arg(ap, t)     (*(t*)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
    #define va_end(ap)        ((void)(ap = (va_list)0))
    #define va_start(ap, x) va_start_a(ap, x)