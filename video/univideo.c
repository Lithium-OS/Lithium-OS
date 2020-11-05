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
#include <sys/video.h>
#include <sys/types.h>
sint32_t test_video()
{
    if (g_sysgrap.type != VIDEO_VBE_RGBA32)
    {
        return -VIDEO_E_MNSPD;
    }
    struct pixel_rgba32 *ptr = (struct pixel_rgba32 *)g_sysgrap.base_addr;
    for (size_t i = 0; i < 25; i++)
    {
        for (size_t i = 0; i < g_sysgrap.res_x; i++)
        {
            ptr->r = 0xff;
            ptr->g = 0x00;
            ptr->b = 0x00;
            ptr->a = 0x00;
            ptr++;
        }
    }
    for (size_t i = 0; i < 25; i++)
    {
        for (size_t i = 0; i < g_sysgrap.res_x; i++)
        {
            ptr->r = 0x00;
            ptr->g = 0xff;
            ptr->b = 0x00;
            ptr->a = 0x00;
            ptr++;
        }
    }
    for (size_t i = 0; i < 25; i++)
    {
        for (size_t i = 0; i < g_sysgrap.res_x; i++)
        {
            ptr->r = 0x00;
            ptr->g = 0x00;
            ptr->b = 0xff;
            ptr->a = 0x00;
            ptr++;
        }
    }
    return 0;
}