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
#include<kfrme.h>
#include "rtc.h"
#include <sys/udev.h>
#include<errno.h>
#include <string.h>
#include <console/video.h>
//全局活动设备描述符数组
DEV g_cdev[MAX_DEV_CNT] = {0};
//对RTC设备的读取封装
size_t udev_read_rtc(DEV *dd,void *buf,size_t n)
{
    get_rtc_time(buf);
    return sizeof(rtime_t);
}
//注册设备描述符,将设备描述符加入活动队列
DEV *udev_regdev(DEV dd)
{
    for (size_t i = 0; i < MAX_DEV_CNT; i++)
    {
        if (g_cdev[i].type == DEV_NULL)
        {
            g_cdev[i]=dd;
            klog("udev","registed device major %h               ",dd.major);
            klog("udev","\\__minjor: %h              ",dd.minjor);
            return &(g_cdev[i]);
        }
    }
    klog("udev","rp");
    errno = ENOMEM;
    return NULL;
}
//初始化设备描述符队列,插入RTC设备
void init_udev(void){
    DEV tmp;
    tmp.d_ops->r_dev = udev_read_rtc;
    tmp.major=65535;
    tmp.minjor=0;
    tmp.type=DEV_BLK;
    memset(g_cdev,0,sizeof(DEV)*MAX_DEV_CNT);
    klog("udev","init base dev list & major 65535_0");
    udev_regdev(tmp);
}
//读取设备
size_t udev_read_dev(uint16_t major,uint16_t minjor,void *buf,size_t n){
    for (size_t i = 0; i < MAX_DEV_CNT; i++){
        if(g_cdev[i].major == major && g_cdev[i].minjor == minjor)
            return g_cdev[i].d_ops->r_dev(&(g_cdev[i]),buf,n);
    }
}