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
#pragma once
#ifndef _VIDEO_H_
#define _VIDEO_H_
#include <types.h>
#include <vbe.h>
#define VIDEO_VBE_RGBA32 6
#define VIDEO_E_MNSPD 0xff0001
/*struct pixel_argb32
{
    uint8_t  r, g, b , a;
} __attribute__((__packed__));*/
extern struct grap_info g_sysgrap;
extern void kputchar(uint32_t x, uint32_t y, char chr, uint32_t fcolor, uint32_t bcolor);
extern void kputstr(uint32_t x, uint32_t y, char *chr, uint32_t fcolor, uint32_t bcolor);
extern void kputnum(uint32_t x, uint32_t y, uint32_t num, uint32_t fcolor, uint32_t bcolor);
extern void kputstrc(uint32_t x, uint32_t y, char *chr, uint32_t fcolor, uint32_t bcolor, uint32_t l);
extern void kputwstr(uint32_t x, uint32_t y, wchar_t *chr, uint32_t fcolor, uint32_t bcolor);
extern void kputwchar(uint32_t x,uint32_t y,wchar_t wchr,uint32_t fcolor,uint32_t bcolor);
extern void kputwstrc(uint32_t x, uint32_t y, wchar_t *chr, uint32_t fcolor, uint32_t bcolor, uint32_t l);
#define RED 0x00ff0000
#define GREEN 0x0000ff00
#define BLUE 0x000000ff
#define YELLOW 0x00ffff00
#define CYAN 0x0000ffff
#define PINK 0x00ff00ff
#define WHITE 0x00ffffff
#define BLACK 0x00000000
#define GRAY 0x00aaaaaa
extern struct grap_info g_sysgrap;
struct grap_info
{
    addri_t base_addr;
    uint32_t res_x, res_y;
    uint32_t dep;
    uint32_t type;
};
#endif