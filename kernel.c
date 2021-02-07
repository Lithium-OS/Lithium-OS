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
#include <sys/multiboot.h>
#include <types.h>
#include <io/port.h>
#include <sys/sysop.h>
#include <console/video.h>
#include <console/tty.h>
#include <sys/interrupt.h>
#include <mm/mem.h>
#include <keyboard.h>
#include <io/ata.h>
#include <fs/fsops.h>
#include <sys/udev.h>
#include <string.h>
#include "build.h"
extern uint32_t fb_addr;
extern uint32_t mem_info;
extern char logo_cpu[];
uint32_t g_time = 0;
int kmain()
{
    
    __asm__("movl $0x8000000,%eax");
    __asm__("movl %eax,%ebp");
    __asm__("movl %eax,%esp");
    g_sysgrap.base_addr = fb_addr;
    g_sysgrap.res_x = 1024;
    g_sysgrap.res_y = 768;
    klog("kernel","this version of kernel is built at");
    klog("kernel",BUILD_TIME);
    klog("kernel","init ebp&esp -> 0xa000000(160M)");
    klog("kernel","init vga -> 1024x768@?hz");
    klog("kernel","start to init");
    init_pit();
    init_interrupt();
    //out_port8(0x21,0xff);//BACU
    init_mem();
    init_slab();
    init_vfs();
    struct vfs_fsnode tnode;
    memcpy(tnode.mount_pt,"/dev/null/",10);
    vfs_insertfs(tnode);
    vfs_unloadfs(1);
    init_udev();
    char buf[50];
    udev_read_dev(65535,0,buf,233);
    klog("kernel","ppp %h",*((int *)buf));
    //memcpy(tnode.mount_pt,"/",1);
    //vfs_regfs(tnode);
    init_rtc();
    //memcpy(tnode.mount_pt,"/srv/",5);
    //vfs_regfs(tnode);
    char wdnmd[512] = {0};
    //ata_read_sector(ata_port_slave,1,wdnmd);
    /*for (size_t i = 0; i < 16; i++)
    {
        kputnum(0,5+i,*(((uint32_t *)wdnmd)+i),YELLOW,BLACK);
    }*/
    char * pa = NULL;
    while (1)
    {
        als_keyboard_code();
    }
}
