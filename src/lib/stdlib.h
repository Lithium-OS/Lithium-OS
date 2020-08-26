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
/*MainDevloper: AlexCui*/
/*ISO C std Lib*/
#ifndef _C_MATH_H_
#define _C_MATH_H_

#include "./stdint.h"

typedef unsigned long long size_t;

int abs(int x);
long labs(long x);
//intmax_t imaxabs(intmax_t x);
#ifdef __cplusplus
#define NULL 0
#else
#define NULL (void *)0
#endif
#endif
