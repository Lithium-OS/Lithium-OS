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
#ifndef _RTC_H_
#define _RTC_H_

#include<kfrme.h>
//初始化RTC并输出时间
extern void init_rtc(void);
//BCD码模式下真实时间格式
typedef struct
{
    uint32_t yr,mo,dy,hr,min,sec;
}rtime_t;
//获取RTC时间
extern int get_rtc_time(rtime_t *time);
#endif