/* Copyright (C) 2020 LithiumOS-Team
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
    auint32_t with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <types.h>
#ifndef _VBE_H_
#define _VBE_H_
//Get the framebuffer base address
extern addr_t *get_vbe_vbuf(char *ptr_vbi, char *ptr_vmi);
//Get the width
extern uint32_t get_vbe_xres(char *ptr_vbi, char *ptr_vmi);
//Get the height
extern uint32_t get_vbe_yres(char *ptr_vbi, char *ptr_vmi);
//Get the pixel depth
extern uint32_t get_vbe_pdep(char *ptr_vbi, char *ptr_vmi);
//initialization VBE video (g_sysgrap)
extern int init_vbe(char *ptr_vbi, char *ptr_vmi);
extern struct grap_info g_sysgrap;
struct grap_info
{
    addri_t base_addr;
    uint32_t res_x, res_y;
    uint32_t dep;
    uint32_t type;
};
#endif