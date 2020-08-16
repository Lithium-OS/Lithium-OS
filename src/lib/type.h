#ifndef _TYPE_H
#define _TYPE_H

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef signed int sint32_t;
typedef signed short sint16_t;
typedef signed char sint8_t;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL   ((void *)0)
#endif
#endif

#endif