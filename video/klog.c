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
#include <sys/sysop.h>
#include <stdarg.h>
char klog_buf[4096][128] = {0};
uint32_t buf_ptr = 0;
static void rklog(char* mod,char* info){
    char bufn[128] = {'[','0',']'};
    strcat(strcat(strcat(bufn,mod),":"),info);
    strncpy(klog_buf[buf_ptr++],bufn,128);
    klog_flsh();
}
void panic(char* mod,char* info,...)
{
    char bufn[128] = {'P',' ',' '};
    strcat(strcat(strcat(bufn,mod),":"),info);
    strncpy(klog_buf[buf_ptr++],bufn,128);
    klog_flsh();
    klog("panic","dumping system infomation");
    klog("panic","kernel halted");
    __asm__("cli");
    hlt_cpu();
}
void klog(char* mod,char* info,...)
{
    va_list vlst;
    size_t cnt = 0;
    //kputnum(0,0,strlen(info),BLUE,BLACK);
    
   /* for (size_t i = 0; i < strlen(info); i++)
    {
        if(*(info+i) == (char)'%')
        {
            cnt++;
            //kputnum(0,i+1,*(info+i),YELLOW,BLACK);
            continue;
        }
        else if(*(info+i) == 0)
            break;  
        //kputnum(0,i+1,*(info+i),GREEN,BLACK);
    }*/
    va_start(vlst,info);
    for (size_t i = 0; i < SIZE_T_MAX; i++)
    {
        if(info[i] == '%')
        {
          //  kputnum(0,i+1,*(info+i),BLUE,BLACK);
            i++;
            char tmp[12] = {"0x????????\0\0"};
            switch (info[i])
            {
            case 'h':
                strdel(info,i,1);
                strins(info,num2str32(tmp,va_arg(vlst,size_t)),i);
                break;
            }
        }
        if (info[i]==0)
        {
            break;
        }
        
    }
        /*else if(info[i] == '\\')
        {
            strdel(info,i,1);
            i++;
        }*/
    rklog(mod,info);
    
    //va_end(vlst);
}
void klog_flsh(){
    if(buf_ptr > 35)
    {
        for (size_t i = buf_ptr-35; i < buf_ptr; i++)
        {
            if(klog_buf[i][0] == '[')
                kputstrc(11,i-(buf_ptr-35),klog_buf[i],WHITE,BLACK,80);
            if(klog_buf[i][0] == 'P')
                kputstrc(11,i-(buf_ptr-35),klog_buf[i],RED,BLACK,80);
        }
    }
    else
    {
        for (size_t i = 0; i < 35; i++)
        {
            if(klog_buf[i][0] == '[')
                kputstrc(11,i,klog_buf[i],WHITE,BLACK,80);
            if(klog_buf[i][0] == 'P')
                kputstrc(11,i,klog_buf[i],RED,BLACK,80);
        }
    }
    
}