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
#include <gccm.h>
#include <sys/types.h>
#ifndef _VIDEO_H_
#define _VIDEO_H_
#define VIDEO_VBE_RGBA32 6
#define VIDEO_E_MNSPD 0xff0001
struct pixel_rgba32
{
    uint8_t r,g,b,a;
}SRT_PACKED;

#include <sys/vbe.h>
#endif