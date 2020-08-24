 /* Copyright (C) 2020 LithiumOS-Team

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
#include "memory.h"
#include "../lib/limits.h"
#include "../kernel/err.h"
#include "../lib/stdlib.h"
uint32_t cnt_pagedes = 0;
extern void sys_cli(void);
extern void sys_sti(void);
uint32_t init_memory(){
    sys_cli();//致命操作的中断保护
    void* page_ptr = (void*)0x8904;  //页表指针初始化
    void* cnt_ptr = (void*)0x8600;        //内存表计数指针
    void* memtab_ptr = (void*)0x8604; //内存表指针初始
    uint32_t page = 0; 
    uint32_t cnt_sec;

    mem_table mtb;  //临时内存表
    mem_pagedes emp_page; //空表模板
    emp_page.attr = 0b00001000;     //属性Clean
    emp_page.pid = UNIT_MAX;  //pid = UINT_MAX  
    for (uint32_t i = 0; i < *(uint32_t*)cnt_ptr; i++){ //循环表项次
        mtb = *((mem_table*)memtab_ptr);
        if (mtb.attr == 1){
            for (uint32_t i = 0; i < (mtb.len / 4096); i++){//循环内存表所需页表次
                emp_page.addr = 0x00 + (page * 4096); //要写入的页表目标地址
                *((mem_pagedes*)page_ptr) =  emp_page; //写入页表
                page_ptr = (uint32_t*)(((uint32_t)page_ptr) + 7);//自增7Byte(长度)
                ++page; //页表计数自增
            }
        
        }
        memtab_ptr = (uint32_t*)(((uint32_t)memtab_ptr) + 24); //内存描述表自增 24Byte
    }
    cnt_pagedes = (page + 1); //写页表计数
    return 0;
    sys_sti();
}
mem_pagedes* get_mem_page(uint32_t num){
    mem_pagedes* page_ptr = (mem_pagedes*)0x8904; //分页表指针
    uint32_t* cnt_ptr = (void*)0x8600;        //内存表计数指针
    mem_pagedes table;
    mem_pagedes* first_ptr = (void*)0x00;
    uint32_t cnt = 0;
    while (cnt <= cnt_pagedes)  //计数小于总页表量
    {

        if(0 ==(page_ptr->addr & 0x08)){    //找到个clean的块
            first_ptr = page_ptr;           //先保存首地址
            for (uint32_t i = 0; i < num; i++)  //向后连续找num个块
            {
                if(0 != (page_ptr->addr & 0x08))//如果不干净
                    goto NextLoop;  //退出循环
                page_ptr = (uint32_t*)(((uint32_t)page_ptr) + 7); //自增
                ++cnt; 
            } 
            return first_ptr; //如果干净的找完指定的页数则返回头页数
        }
NextLoop:
        ++cnt;   
        page_ptr = (uint32_t*)(((uint32_t)page_ptr) + 7);//自增7Byte(长度) 
    }
    errno = ENOMEM;
    return NULL;
}

mem_pagedes* alloc_mem_page(uint16_t pid,uint32_t num){
    sys_sli(); //致命操作的中断保护
    mem_pagedes* rtn;
    rtn = get_mem_page(num); //get到连续内存块
    if (rtn != NULL){ //如果存在
        for (size_t i = 0; i < num; i++) //连续设置num块
        {
            if (pid != 0)//如果是用户申请 (pid!=0)
                (rtn + i)->attr = (((rtn + i)->attr | 0x0a) ^ 0x08); //去除Clean设置Busy
            else
                (rtn + i)->attr = (((rtn + i)->attr | 0x0e) ^ 0x08); //去除Clean设置Busy和Kernel
        }
        return rtn; //返回首块
    }
    else{           //如果不存在
        return NULL;    //返回NULL
    }
    sys_sti();
}
