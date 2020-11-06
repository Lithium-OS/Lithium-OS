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
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <types.h>
#include <vbe.h>
struct grap_info g_sysgrap;
addr_t *get_vbe_vbuf(char *ptr_vbi, char *ptr_vmi)
{
    if (ptr_vbi[0] == 'V' && ptr_vbi[1] == 'E' && ptr_vbi[2] == 'S' && ptr_vbi[3] == 'A')
    {
        return (addr_t *)((uint32_t *)ptr_vmi)[40 / 4];
    }
    else
        return 0;
}
uint32_t get_vbe_xres(char *ptr_vbi, char *ptr_vmi)
{
    if (ptr_vbi[0] == 'V' && ptr_vbi[1] == 'E' && ptr_vbi[2] == 'S' && ptr_vbi[3] == 'A')
    {
        return (uint32_t)((uint16_t *)ptr_vmi)[18 / 2];
    }
    else
        return 0;
}
uint32_t get_vbe_yres(char *ptr_vbi, char *ptr_vmi)
{
    if (ptr_vbi[0] == 'V' && ptr_vbi[1] == 'E' && ptr_vbi[2] == 'S' && ptr_vbi[3] == 'A')
    {
        return (uint32_t)((uint16_t *)ptr_vmi)[20 / 2];
    }
    else
        return 0;
}
uint32_t get_vbe_pdep(char *ptr_vbi, char *ptr_vmi)
{
    if (ptr_vbi[0] == 'V' && ptr_vbi[1] == 'E' && ptr_vbi[2] == 'S' && ptr_vbi[3] == 'A')
    {
        return (uint32_t)ptr_vmi[25];
    }
    else
        return 0;
}
int init_vbe(char *ptr_vbi, char *ptr_vmi)
{
    g_sysgrap.base_addr = (addri_t)get_vbe_vbuf(ptr_vbi, ptr_vmi);
    g_sysgrap.res_x = get_vbe_xres(ptr_vbi, ptr_vmi);
    g_sysgrap.res_y = get_vbe_yres(ptr_vbi, ptr_vmi);
    g_sysgrap.base_addr = get_vbe_pdep(ptr_vbi, ptr_vmi);
    g_sysgrap.type = ptr_vbi[27];
    return 0;
}