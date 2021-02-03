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
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _UDEV_H_
#define _UDEV_H_
#define DEV_NULL 0
#define DEV_BLK 1
#define DEV_CHR 2
#define MAX_DEV_CNT 128
extern void init_udev(void);
extern size_t udev_read_dev(uint16_t major,uint16_t minjor,void *buf,size_t n);
#include "../dev/udev.h"
#endif