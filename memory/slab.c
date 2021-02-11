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
#include <mm/mem.h>
#include "slab.h"
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include<console/video.h>
#include<sys/sysop.h>
struct slab_pool *mp_ptr;
struct slab_pool *now;
const uint32_t slab_sizec[16] = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
int slab_addslab(struct slab_pool *pool)
{
    struct slab *ptr = pool->header;
    for (size_t i = 0; i < pool->slab_cnt; i++)
        if (ptr->next != NULL)
            ptr = ptr->next;
        else
            break;
    for (size_t i = 0; i < 4096 / sizeof(struct slab); i++)
    {
        if (pool->header[i].page_cnt == 0)
        {
            pool->header[i].last = ptr;
            ptr->next = ptr;
            ptr = ptr->next;
            ptr->page_cnt = (4096 / pool->page_size);
            ptr->page_free = (4096 / pool->page_size);
            ptr->buf = kpmalloc((slab_sizec[i] / 4096 + 1));
            ptr->next = NULL;
            pool->slab_cnt++;
            memset(ptr->cmap, 0, 16);
            return 0;
        }
    }
    return -1;
}
int slab_recyslab(struct slab_pool *pool)
{
    struct slab *ptr = pool->header;
    for (size_t i = 0; i < pool->slab_cnt; i++)
        if (ptr->page_free != ptr->page_cnt)
            ptr = ptr->next;
        else
            break;
    if (ptr->next != NULL)
        ptr->next->last = ptr->last;
    if (ptr->last != ptr)
        ptr->last->next = ptr->next;
    for (size_t i = 0; i < slab_sizec[i] / 4096 + 1; i++)
        kpfree(((char *)ptr->buf) + i * 4096);
    ptr->page_cnt = 0;
    pool->slab_cnt--;
}
void *slab_malloc(size_t n)
{
    for (size_t i = 0; i < 16; i++) //遍历尺寸表
        if (slab_sizec[i] >= n)
        {
            struct slab *ptr = mp_ptr[i].header;
#define now_node ptr
            kputnum(0,0,mp_ptr,GREEN,BLACK);
            for (size_t n = 0; n < mp_ptr[i].slab_cnt; n++)
            {
                if (ptr->page_free != 0)
                    for (size_t _l = 4; _l > 0; _l--) //对位图进行逐int扫描
                    #define l (_l-1)
                        if (now_node->cmap[l] != 0xffffffffUL)
                            for (size_t k = 0; k < 4; k++)
                                if (((now_node->cmap[l] & (0xff << k * 8))) != 0xff) //对位图进行逐char扫描
                                    for (size_t m = 0; m < 8; m++)
                                        if ((((now_node->cmap[l]) & (0xff << k * 8)) & (1 << m)) != 1)                                 //对位图进行逐bit扫描
                                            if ((4-l) * 32 + k * 8 + m <= now_node->page_cnt) //判断该位位置是否超过该slab最大页面数
                                            {
#define off_bit ((4-l) * 32 + k * 8 + m)
                                                now_node->page_free--;
                                                if (off_bit < 32)
                                                    now_node->cmap[3] |= 1 << off_bit;
                                                else if (off_bit < 64)
                                                    now_node->cmap[2] |= 1 << off_bit - 32;
                                                else if (off_bit < 96)
                                                    now_node->cmap[1] |= 1 << off_bit - 64;
                                                else if (off_bit < 128)
                                                    now_node->cmap[0] |= 1 << off_bit - 96;
                                                return (((char *)now_node->buf) + off_bit*mp_ptr[i].page_size);
                                                //
#undef off_bit
                                            }
                ptr = ptr->next;
            }
            if (slab_addslab(((struct slab_pool *)(mp_ptr + i))) == 0)
                return slab_malloc(n);//The function of that things is add a new slab to slab_pool when all slab is full

            errno = ENOMEM;
            #undef l
        }
#undef now_node6
    errno = E2BIG;
    return NULL;
}
void slab_free(void *addr)
{
    for (size_t i = 0; i < 16; i++)
    {
        struct slab *ptr = mp_ptr[i].header;
        do
        {
            if (ptr->buf - addr < 4096)
            {
                if (((ptr->buf - addr) / mp_ptr[i].page_size) < 32)
                    ptr->cmap[3] ^= 1 << ((ptr->buf - addr) / mp_ptr[i].page_size);
                else if (((ptr->buf - addr) / mp_ptr[i].page_size) < 64)
                    ptr->cmap[2] ^= 1 << ((ptr->buf - addr) / mp_ptr[i].page_size) - 32;
                else if (((ptr->buf - addr) / mp_ptr[i].page_size) < 96)
                    ptr->cmap[1] ^= 1 << ((ptr->buf - addr) / mp_ptr[i].page_size) - 64;
                else if (((ptr->buf - addr) / mp_ptr[i].page_size) < 128)
                    ptr->cmap[0] ^= 1 << ((ptr->buf - addr) / mp_ptr[i].page_size) - 96;
                ptr->page_free++;
                if (ptr->page_free == ptr->page_cnt)
                    slab_recyslab(((struct slab_pool *)(mp_ptr + i)));
                return;
            }
            ptr = ptr->next;
        } while (ptr->next != NULL);
    }
}
void init_slab()
{
    //申请slab_pool页面空间
    mp_ptr = kpmalloc(1);
    kputstr(0,5,mp_ptr,YELLOW,BLACK);
    now = mp_ptr;
    memset(mp_ptr, 0, 4096);
    kputnum(0,8,mp_ptr,RED,YELLOW);
    //初始化首节点
    //初始化slab池slab链表空间
    mp_ptr->header = kpmalloc(1);
    memset(mp_ptr->header, 0, 4096);
    mp_ptr->last = mp_ptr;
    //初始化slab池slab头指向的可分配区域
    now->header->buf = kpmalloc(1);
    memset(mp_ptr->header->buf, 0, 4096);
    memset(now->header->cmap, 0, 36);
    now->header->last = now->header;

    for (size_t i = 1; i < 16; i++)
    {
        //设置链表指针
        (now + 1)->last = now;
        now->next = (now + 1);
        //跳转到下一个
        now = (now + 1);
        //初始化节点
        //初始化slab池slab链表空间
        now->header = kpmalloc(1);
        memset(now->header, 0, 4096);
        //初始化slab池slab头指向的可分配区域
        now->header->buf = kpmalloc(slab_sizec[i] / 4096 + 1);
        //计算页面计数
        now->page_size = slab_sizec[i];
        now->slab_cnt = 1;
        now->header->page_free = slab_sizec[i] < 4096 ? 4096 / slab_sizec[i] : slab_sizec[i] /4096 ;
        now->header->page_cnt = slab_sizec[i] < 4096 ? 4096 / slab_sizec[i] : slab_sizec[i] /4096 ;
        now->slab_cnt = 1;
    }
}