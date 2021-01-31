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
#define MOUNT_PT_LEN 30
#define P4KB_MAX_NODE 84

#define NULL_FS 0
#define LIFSRD_FS 1

#define TYPE_DIR 0
#define TYPE_FILE 1
#include<errno.h>

extern int path_type(char* path);

typedef struct
{
    char path[128];
    uint32_t ouid,ogid;
    uint32_t prem;
    uint16_t type;
    time_t ctime,mtime,atime;
}FILE;

typedef struct
{
    uint16_t major,minjor;
}DEV;
struct vfs_i_sops
{
    int (*c_file)(DEV *dev,FILE *fd,uint32_t uid,uint32_t gid);
    int (*rm_file)(DEV *dev,FILE *fd,uint32_t uid,uint32_t gid);
    int (*r_file)(DEV *dev,FILE *dst,void *buf,size_t n,uint32_t uid,uint32_t pid);
    int (*w_file)(DEV *dev,FILE *dst,void *buf,size_t n,uint32_t uid,uint32_t pid);
    int (*rattr_file)(DEV *dev,FILE *fd,FILE *dst,uint32_t uid,uint32_t gid);
};
struct vfs_f_ops
{
    struct vfs_i_sops i_ops;
};

struct vfs_fsnode;
struct vfs_fsnode{
    char mount_pt[MOUNT_PT_LEN]; // align to 48 byte
    uint32_t major;
    uint16_t type;
    struct vfs_fsnode *next;
    struct vfs_fsnode *last;
    struct vfs_fs_ops *ops;
    
};

#endif