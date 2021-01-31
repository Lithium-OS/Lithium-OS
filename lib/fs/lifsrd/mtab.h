/* Copyright (C) 2020-2021 AlanCui
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
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#ifndef _LIFSRD_H_
#define _LIFSRD_H_

#define BS_2KB 0
#define BS_4KB 1
typedef struct {
    char name[128];
    uint32_t ent_type;
    uint32_t drv_major,drv_minjor;
    uint32_t ent_size;
    uint32_t cluser[90] //256bytes align
}lifsrd_mentry;
typedef struct {
    char vol_name[64];
    uint16_t bs_type;
    uint32_t cluser_num;
    lifsrd_mentry entry[127];//32768 align
}lifsrd_header;
#endif