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
#include <console/video.h>
#include <types.h>
#include<string.h>
char klog_buf[4096][128] = {0};
uint32_t buf_ptr = 0;
void klog(char* mod,char* info){
    char bufn[128] = {'[','0',']'};
    strncpy(klog_buf[buf_ptr++],strcat(strcat(strcat(bufn,mod),":"),info),128);
    klog_flsh();
}
void klog_flsh(){
    if(buf_ptr > 35)
    {
        for (size_t i = buf_ptr-35; i < buf_ptr; i++)
        {
            if(klog_buf[i][0] == '[')
                kputstrc(0,i-(buf_ptr-35),klog_buf[i],WHITE,BLACK,80);
        }
    }
    else
    {
        for (size_t i = 0; i < 35; i++)
        {
            if(klog_buf[i][0] == '[')
                kputstrc(0,i,klog_buf[i],WHITE,BLACK,80);
        }
    }
    
}