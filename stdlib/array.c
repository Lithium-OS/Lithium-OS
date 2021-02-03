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

#include <kfrme.h>
#include <bool.h>
#include <mm/mem.h>

/*
array库


*/

typedef uint32_t ADT;

typedef struct Array {
    uint32_t N;
    ADT *arr;
}array;

void array_init(array *obj,uint32_t size) {
    obj->N=size;
    obj->arr=(ADT*)kpmalloc();
}

ADT *array_at(array *obj,uint32_t idx) {
    if(idx<0 || idx>=obj->N)
      return NULL;
    ADT *p=&(obj->arr[idx]);
    return p;
}

_Bool array_change(array *obj,uint32_t idx,ADT val) {
    if(idx<0 || idx>=obj->N)
      return false;
    obj->arr[idx]=val;
    return true;
}

ADT *array_begin(array *obj) {
    return obj->arr;
}

ADT *array_back(array *obj) {
    return &obj->arr[obj->N-1];
}

ADT *array_end(array *obj) {
    return &obj->arr[obj->N];
}

_Bool array_fill(ADT *head,ADT *tail,ADT val) {
    if(head>tail)
      return false;
    for(;head!=tail;head++)
      *head=val;
    return true;
}