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
#ifndef _VFS_H_
#define _VFS_H_
#include <kfrme.h>
//挂载点路径最大长度
#define MOUNT_PT_LEN 30
//最大可寻址文件路径长度
#define MAX_LOCTABLE_LEN 4096
//在4KiB页面中最大能存下的文件系统节点数
#define P4KB_MAX_NODE 84
//活动队列最大可被持有文件描述符数
#define MAX_HANDELED_FD 4096

#define NULL_FS 0
#define LIFSRD_FS 1

#define TYPE_NULL 0
#define TYPE_UNINIT 1
#include<errno.h>
//获取路径类型
extern int path_type(char* path);
//获取指定层深的目录
extern char *vfs_getroot(char *spath,size_t depth,char *path);
#include <sys/udev.h>
//系统鉴权结构体
typedef struct 
{
    uid_t uid;
    gid_t gid;
    pid_t pid;
}sprem_t;
//文件描述符
typedef struct
{
    char path[128];
    uint32_t ouid,ogid,hpid;
    uint32_t prem;
    uint16_t type;
    time_t ctime,mtime,atime;
    struct vfs_f_ops *f_ops;
}FILE;
//Inode操作函数组
struct vfs_i_sops
{
    int (*c_file)(DEV *dev,FILE *fd,sprem_t prem);
    int (*rm_file)(DEV *dev,FILE *fd,sprem_t prem);
    int (*r_file)(DEV *dev,FILE *dst,void *buf,size_t n,sprem_t prem);
    int (*w_file)(DEV *dev,FILE *dst,void *buf,size_t n,sprem_t prem);
    int (*ioctl_file)(DEV *dev,FILE *dst,uint32_t func,void *ctl,sprem_t prem);
    int (*rattr_file)(DEV *dev,FILE *fd,FILE *dst,sprem_t prem);
};
//文件操作函数组
struct vfs_f_ops
{
    struct vfs_i_sops i_ops;
    DEV *r_dev;
};

struct vfs_fsnode;
//文件系统节点
struct vfs_fsnode{
    char mount_pt[MOUNT_PT_LEN]; // align to 48 byte
    uint32_t major;
    uint16_t type;
    struct vfs_fsnode *next;
    struct vfs_fsnode *last;
    struct vfs_fs_ops *ops;
    
};

#endif