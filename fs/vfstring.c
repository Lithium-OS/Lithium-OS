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
int path_type(char* path){
    if (path[strlen(path)] == '/')
        return TYPE_NULL;
    else
        return TYPE_NULL;
}
char *vfs_getroot(char *spath, size_t depth, char *path)
{
    strcpy(path, spath);
    size_t of = 0;
    char *pt = path;
    for (size_t i = 0; i < depth; i++)
    {
        pt = strchr(pt, '/') + 1;
    }
    memset(pt, 0, pt - path);
    klog("groot", path);
    return path;
}
