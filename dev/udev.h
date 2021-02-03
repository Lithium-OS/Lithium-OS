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
#ifndef DEV_UDEV_H_
#define DEV_UDEV_H_

#ifndef _UDEV_H_//若未包含全局作用下的udev.h则包含
#include "sys/udev.h"
#endif

#include <kfrme.h>
struct udev_d_ops;
//设备描述符
typedef struct
{
    uint16_t major,minjor,type;
    struct udev_d_ops *d_ops;
}DEV;
//设备操作函数组
struct udev_d_ops
{
    int (*r_dev)(DEV *dd,void *buf,size_t n);
};
#endif