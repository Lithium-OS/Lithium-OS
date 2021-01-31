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
/*Copyright (C) 2020-2021 AlanCui*/
#include <types.h>
#include <io/port.h>
#include <console/video.h>
#include"rtc.h"

#define __get_rtc(addr) ({\
    out_port8(0x70,0x80 | addr);\
    in_port8(0x71);\
})

int get_rtc_time(rtime_t *time)
{
    __asm__("cli");
    do
    {
        time->yr = __get_rtc(0x09) + __get_rtc(0x32) * 0x100;
        time->mo = __get_rtc(0x08);
        time->dy = __get_rtc(0x07);
        time->hr = __get_rtc(0x04);
        time->min = __get_rtc(0x02);
        time->sec = __get_rtc(0x00);
    } while (time->sec != __get_rtc(0x00));
    __asm__("sti");
    return 0;
}
void init_rtc(void)
{
    klog("rtc","get real time from RTC");
    rtime_t tmp;
    get_rtc_time(&tmp);
    klog("rtc","GMT %h yr",tmp.yr);
}