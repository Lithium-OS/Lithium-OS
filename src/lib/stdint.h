// C Standard Library
// stdint.h

#ifndef _C_STDINT_H
#define _C_STDINT_H

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char         int_least8_t;
typedef signed short        int_least16_t;
typedef signed int          int_least32_t;
typedef signed long long    int_least64_t;
typedef unsigned char       uint_least8_t;
typedef unsigned short      uint_least16_t;
typedef unsigned int        uint_least32_t;
typedef unsigned long long  uint_least64_t;

typedef signed char         int_fast8_t;
typedef signed int          int_fast16_t;
typedef signed int          int_fast32_t;
typedef signed long long    int_fast64_t;
typedef unsigned char       uint_fast8_t;
typedef unsigned int        uint_fast16_t;
typedef unsigned int        uint_fast32_t;
typedef unsigned long long  uint_fast64_t;

typedef signed long long    intmax_t;
typedef unsigned long long  uintmax_t;

typedef signed int          intptr_t;
typedef unsigned int        uintptr_t;

#endif
