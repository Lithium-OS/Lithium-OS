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
/*Copyright (C) 2020-2021 LithiumOS Team*/

#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <bits/btypes.h>
#ifdef _cplusplus
extern "C"
{
#define restrict
#endif
typedef uint32_t ADT;

typedef struct Array {
    uint32_t N;
    ADT *arr;
}array;

void array_init(array *obj,uint32_t size);
ADT *array_at(array *obj,uint32_t idx);
_Bool array_change(array *obj,uint32_t idx,ADT val);
ADT *array_begin(array *obj);
ADT *array_back(array *obj);
ADT *array_end(array *obj);
_Bool array_fill(ADT *head,ADT *tail,ADT val);
#ifdef __cplusplus
}
#endif
#endif

