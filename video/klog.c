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
#include <time.h>
#include <io/port.h>
void klog_flsh();
char klog_buf[4096][128] = {0};
uint32_t buf_ptr = 0;
static void rklog(char* mod,char* info){
    char bufn[128] = {'['};
    char tmp[12] = {"0x????????\0\0"};
    strcat(bufn,num2str32(tmp,g_kmaincnt));
    strcat(bufn,"]");
    strcat(strcat(strcat(bufn,mod),":"),info);
    strncpy(klog_buf[buf_ptr++],bufn,128);
    out_port16(0x3f8,'\n');
    for(size_t i = 0;i < 128;i++)
        out_port16(0x3f8,(uint16_t)klog_buf[buf_ptr-1][i]);
    klog_flsh();
}
void panic(char* mod,char* info,...)
{
    __asm__("cli");
    char bufn[128] = {'P',' ',' '};
    strcat(strcat(strcat(bufn,mod),":"),info);
    strncpy(klog_buf[buf_ptr++],bufn,128);
    klog_flsh();
    klog("panic","dumping system infomation");
    klog("panic","kernel halted");
    hlt_cpu();
}
void klog(char* mod,char* info,...)
{
    char bufn[128] = {'['};
    char tmp[12] = {"0x????????\0\0"};
    va_list vlst;
    size_t cnt = 0;
    strcat(bufn,num2str32(tmp,g_kmaincnt));
    strcat(bufn,"]");
    strcat(strcat(bufn,mod),":");
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
    size_t f=strlen(bufn);
    for (size_t i = 0; i < 128;)
    {
        if(info[i] == '%')
        {
            out_port16(0x3f8,'@');
          //  kputnum(0,i+1,*(info+i),BLUE,BLACK);
            char tmpd[12] = {"0x????????\0"};
            char tmpw[12] = {"0x????\0"};
            switch (info[i+1])
            {
            case 'h':
                strcpy(&(bufn[f]),num2str32(tmpd,va_arg(vlst,size_t)));
                f += 11;
                i +=3;
                break;
            case 'w':
                strcpy(&(bufn[f]),num2str16(tmpw,va_arg(vlst,uint16_t)));
                f += 6;
                i +=3;
                break;
            case 'm':
                strcpy(&(bufn[f]),num2str16(tmpw,va_arg(vlst,uint16_t)));
                strcat(&(bufn[f]),":");
                strcat(&(bufn[f]),num2str16(tmpw,va_arg(vlst,uint16_t)));
                f += 12;
                i +=3;
                break;
            default:
                break;
            }
        }
        else if (info[i]==0)
        {
            break;
        }
        bufn[f] = info[i];
        i++;
        f++;
    }
        /*else if(info[i] == '\\')
        {
            strdel(info,i,1);
            i++;
        }*/
        out_port16(0x3f8,'\n');
        for(size_t i = 0;i < 128;i++)
            if((uint16_t)klog_buf[buf_ptr-1][i]!=0)
                out_port16(0x3f8,(uint16_t)klog_buf[buf_ptr-1][i]);
    //strncpy(klog_buf[buf_ptr++],bufn,128);
    //out_port16(0x3f8,'\n');
    strncpy(klog_buf[buf_ptr++],bufn,128);
    klog_flsh();
    
    //va_end(vlst);
}
void klog_flsh(){
    if(buf_ptr > 35)
    {
        for (size_t i = buf_ptr-40; i < buf_ptr; i++)
        {
            if(klog_buf[i][0] == '[')
                kputstrc(11,i-(buf_ptr-40),klog_buf[i],WHITE,BLACK,100);
            if(klog_buf[i][0] == 'P')
                kputstrc(11,i-(buf_ptr-40),klog_buf[i],RED,BLACK,100);
        }
    }
    else
    {
        for (size_t i = 0; i < 40; i++)
        {
            if(klog_buf[i][0] == '[')
                kputstrc(11,i,klog_buf[i],WHITE,BLACK,100);
            if(klog_buf[i][0] == 'P')
                kputstrc(11,i,klog_buf[i],RED,BLACK,100);
        }
    }
    
}