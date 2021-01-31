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
#include <kfrme.h>
#include <console/tty.h>
#include <mm/mem.h>
#include "vfs.h"
#include <string.h>
struct vfs_fsnode *g_vfsfs;
uint32_t g_dmajor_fs = 0;
void init_vfs(void)
{
    g_vfsfs = kpmalloc();
    klog("vfs","set g_vfsfs -> %h          ",g_vfsfs);
    struct vfs_fsnode tmp;
    memcpy(tmp.mount_pt,"NULL",4);
    tmp.major=UINT_MAX;
    tmp.type=SHORT_MAX;
    tmp.next=NULL;
    tmp.last=NULL;
    *g_vfsfs = tmp;
    klog("vfs","insert a NULL node to vfs");
}
int vfs_regfs(struct vfs_fsnode node)
{
    struct vfs_fsnode *ptr = g_vfsfs;  
    for (size_t i = 0; i < P4KB_MAX_NODE; i++)
    {
        if (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        else
        {
            //if (path_type(node.mount_pt) != TYPE_DIR)
              //  return -EISDIR;  
            *(ptr+1) = node;
            ptr->next = (ptr+1);
            (ptr+1)->last = ptr;
            ptr++;
            ptr->major = ++g_dmajor_fs;
            char tmp[MOUNT_PT_LEN + 3] = {"at:"};
            klog("vfs","registed filesystem major:%h                    ",ptr->major);
            klog("      \\__",strcat(tmp,ptr->mount_pt));
            return ptr->major;
        }
        
    }
    return -1;   
}
int vfs_unloadfs(uint32_t major)
{
  struct vfs_fsnode *ptr = g_vfsfs;  
    for (size_t i = 0; i < P4KB_MAX_NODE; i++)
    {
        if (ptr->major == major)
        {
            ptr->last->next = ptr->next;
            ptr->next->last = ptr->last;
            ptr->major = UINT_MAX;
            ptr->type = USHORT_MAX;
            ptr->next = NULL;
            ptr->last = NULL;
            char tmp[MOUNT_PT_LEN + 3] = {"at:"};
            klog("vfs","unloaded filesystem major:%h                    ",major);
            klog("      \\__",strcat(tmp,ptr->mount_pt));
            return 0;
        }
        else
        {
            ptr = ptr->next;
        }
        
    }  
    return -ENOENT;
};