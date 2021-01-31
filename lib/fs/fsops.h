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
#ifndef _FSOPS_H_
#define _FSOPS_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include"../../fs/vfs.h"
extern void init_vfs(void);
extern int vfs_regfs(struct vfs_fsnode node);
extern int vfs_unloadfs(uint32_t major);
#ifdef __cplusplus
}
#endif
#endif