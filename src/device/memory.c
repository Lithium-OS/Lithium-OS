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
/*MainDevloper: AlanCui*/
/*NotFin*/
#include "memory.h"
#include "./kernel/err.h"
#include "../lib/limits.h"
#include "../kernel/err.h"
#include "../lib/stdlib.h"
mem_pagedes mempage_des_table[1048576];
uint32_t cnt_pagedes = 0;
extern void sys_cli(void);
extern void sys_sti(void);
uint32_t init_memory(){
    sys_cli();//致命操作的中断保护
    void* cnt_ptr = (void*)0x8600;        //内存表计数指针
    void* memtab_ptr = (void*)0x8604; //内存表指针初始
    uint32_t page = 0; 
    uint32_t cnt_sec;

    mem_table mtb;  //临时内存表
    mem_pagedes emp_page; //空表模板
    emp_page.attr = 0b00001000;     //属性Clean
    emp_page.pid = UNIT_MAX;  //pid = UINT_MAX 
    //emp_page.b_ptr = 0; //清除byte分配指针 
    for (uint32_t i = 0; i < *(uint32_t*)cnt_ptr; i++){ //循环表项次
        mtb = *((mem_table*)memtab_ptr);
        if (mtb.attr == 1){
            for (uint32_t i = 0; i < (mtb.len / 4096); i++){//循环内存表所需页表次
                emp_page.addr = mtb.base + (page * 4096); //要写入的页表目标地址
                mempage_des_table[page] =  emp_page; //写入页表
                ++page; //页表计数自增
            }
        
        }
        memtab_ptr = (uint32_t*)(((uint32_t)memtab_ptr) + 24); //内存描述表自增 24Byte
        page = 0;
    }
    cnt_pagedes = (page + 1); //写页表计数
    return 0;
    sys_sti();
}
uint32_t get_mem_page(uint32_t num){
    uint32_t* cnt_ptr = (void*)0x8600;        //内存表计数指针
    mem_pagedes table;
    uint32_t first_ptr ;
    uint32_t cnt = 0;
    while (cnt <= cnt_pagedes)  //计数小于总页表量
    {

        if(0 ==(mempage_des_table[cnt].attr & 0x08)){    //找到个clean的块
           first_ptr = cnt;         //先保存首地址
            for (uint32_t i = 0; i < num; i++)  //向后连续找num个块
            {
                if(0 != (mempage_des_table[cnt].attr & 0x08))//如果不干净
                    goto NextLoop;  //退出循环
                ++cnt; 
            } 
            return first_ptr; //如果干净的找完指定的页数则返回头页数
        }
NextLoop:
        ++cnt;   
    }
    errno = ENOMEM;
    return NULL;
}

void* alloc_mem_page(uint16_t pid,uint32_t num){
    sys_sli(); //致命操作的中断保护
    uint32_t rtn;
    rtn = get_mem_page(num); //get到连续内存块
    if (rtn != NULL){ //如果存在
        for (size_t i = 0; i < num; i++) //连续设置num块
        {
            if (pid != 0)//如果是用户申请 (pid!=0)
                mempage_des_table[rtn].attr = ((mempage_des_table[rtn].attr | 0x0a) ^ 0x08); //去除Clean设置Busy
            else
                mempage_des_table[rtn].attr = ((mempage_des_table[rtn].attr | 0x0e) ^ 0x08); //去除Clean设置Busy和Kernel
            if (i == 0)
                mempage_des_table[rtn].len_ptr = num;  //如果为首Block设置后页计数
            else
                mempage_des_table[rtn].len_ptr = 0x0fffffff; //如果不是首页就设置为0x0fffffff
            
            
        }
        sys_sti();
        return mempage_des_table[rtn].addr; //返回首块
    }
    else{           //如果不存在
        sys_sti();
        return NULL;    //返回NULL
    }
    
}

uint32_t free_mem_page(void* ptr){
    if (mempage_des_table[((uint32_t)ptr / 4096)].len_ptr != 0x0fffffff) //判断是否为首Block
    { //执行释放操作
        for (uint32_t i = (((uint32_t)ptr) / 4096); i < mempage_des_table[((uint32_t)ptr / 4096)].len_ptr; i++)
        {
           mempage_des_table[i].attr = ((mempage_des_table[i].attr & 0) | 0x08);// 清ALL设置Clean
        }
        return 0;
    }
    else
    {//报告内存Block错误的致命错误
        errno = EFAULT;
        return NULL;
    }
    
}

void* alloc_mem_byte(void* ptr,uint32_t cnt){
    void* rtn; //创建返回指针
    rtn = mempage_des_table[((uint32_t)ptr / 4096)].addr;//将指针移到该表项的头
    //rtn = rtn + mempage_des_table[((uint32_t)ptr / 4096)].b_ptr;//将指针移位至已经分配的内存后
    //if ((mempage_des_table[((uint32_t)ptr / 4096)].b_ptr + cnt) > 4096) //判断是否还有MEM
    {//如果有
       // mempage_des_table[((uint32_t)ptr / 4096)].b_ptr = cnt + mempage_des_table[((uint32_t)ptr / 4096)].b_ptr; //b_ptr自增
        rtn = rtn + cnt;//rtn自增
        return rtn;
    }
    //else
    {
        errno = ENOMEM;
        return NULL; //报告无内存致命错误
    }
    
}

uint32_t free_mem_byte(void* ptr,uint32_t cnt)