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
//全局文件系统节点链表头
struct vfs_fsnode *g_vfsfs;
//全局文件系统节点MAJOR计数
uint32_t g_dmajor_fs = 0;
//全局活动文件描述符列表
FILE g_handled_fd[MAX_HANDELED_FD];
//初始化VFS
void init_vfs(void)
{
    //申请4KB页面,将链表头指向页面
    g_vfsfs = kpmalloc(1);
    klog("vfs", "set g_vfsfs -> %h          ", g_vfsfs);
    struct vfs_fsnode tmp;
    memcpy(tmp.mount_pt, "NULL", 4);
    tmp.major = UINT_MAX;
    tmp.type = SHORT_MAX;
    tmp.next = NULL;
    tmp.last = NULL;
    *g_vfsfs = tmp;
    //初始化链表头为NULL节点
    klog("vfs", "insert a NULL node to vfs");
}
//插入文件描述符到活动列表
FILE *vfs_insertfd(char *path, sprem_t prem)
{
    FILE tmp;
    tmp.hpid = prem.pid;//设置节点PID值,状态设置为未初始化
    tmp.type = TYPE_UNINIT;
    size_t i = 0;
    for (i = 0; i < MAX_HANDELED_FD; i++)//遍历活动文件描述符数组
        if (g_handled_fd[i].type == TYPE_NULL)
        {
            g_handled_fd[i] = tmp;
            return &(g_handled_fd[i]);
        }
        else if (!strcmp(g_handled_fd[i].path, path))
        {
            errno = EBUSY;
            return NULL;
        }
    errno = EMFILE;
    return NULL;
}
//从活动列表卸载文件描述符
void vfs_unloadfd(FILE *fd, sprem_t prem)
{
    if (fd->hpid == prem.pid)
        fd->type = TYPE_NULL;
    else
        errno = EACCES;
    return;
}
//将文件系统节点插入活动链表
int vfs_insertfs(struct vfs_fsnode node)
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
            *(ptr + 1) = node;
            ptr->next = (ptr + 1);
            (ptr + 1)->last = ptr;
            ptr++;
            ptr->major = ++g_dmajor_fs;
            char tmp[MOUNT_PT_LEN + 3] = {"at:"};
            klog("vfs", "registed filesystem major:%h                    ", ptr->major);
            klog("      \\__", strcat(tmp, ptr->mount_pt));
            return ptr->major;
        }
    }
    return -1;
}
//从活动链表卸载文件系统
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
            klog("vfs", "unloaded filesystem major:%h                    ", major);
            klog("      \\__", strcat(tmp, ptr->mount_pt));
            return 0;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return -ENOENT;
};
//获取指定挂载点的文件系统节点的文件操作符
struct vfs_f_ops *vfs_get_fops(char *mntp)
{
    struct vfs_fsnode *ptr = g_vfsfs;
    for (size_t i = 0; i < P4KB_MAX_NODE; i++)
        if (strcmp(ptr->mount_pt, mntp))
            ptr = ptr->next;
        else
            return ptr->ops;
    errno = ENOENT;
    return 0;
}
//打开指定路径的文件
FILE *vfs_open(char *path, sprem_t prem)
{
    char buf[MAX_LOCTABLE_LEN] = {0};
    for (size_t i = 0; i < 32; i++)
        if (vfs_get_fops(vfs_getroot(path, i, buf)) != NULL)
        {
            FILE *tmp = vfs_insertfd(path, prem);
            tmp->f_ops = vfs_get_fops(vfs_getroot(path, i, buf));
            return tmp;
        }
}
//关闭文件描述符
void vfs_close(FILE *fd, sprem_t prem)
{
    return vfs_unloadfd(fd, prem);
}
//读取文件
size_t vfs_read(FILE *fd,char *buf,size_t n, sprem_t prem)
{
    return fd->f_ops->i_ops.r_file(fd->f_ops->r_dev,fd,buf,n,prem);
}
//写入文件
size_t vfs_write(FILE *fd,char *buf,size_t n, sprem_t prem)
{
    return fd->f_ops->i_ops.w_file(fd->f_ops->r_dev,fd,buf,n,prem);
}
//对文件进行I/O控制操作
size_t vfs_ioctl(FILE *fd,uint32_t func,char *ctl, sprem_t prem)
{
    return fd->f_ops->i_ops.ioctl_file(fd->f_ops->r_dev,fd,func,ctl,prem);
}
