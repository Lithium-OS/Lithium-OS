/* Copyright (C) 2020-2021 AlanCui
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
#include <console/video.h>
#include <types.h>
extern uint8_t unifont[65534][32];
struct grap_info g_sysgrap;
void kputchar(uint32_t x, uint32_t y, char chr, uint32_t fcolor, uint32_t bcolor)
{
    addr_t *target_addr = (void *)(g_sysgrap.base_addr + (y * g_sysgrap.res_x * 32 * 2 + x * 32));
    if (chr == 0x00)
        chr = ' ';
    for (size_t i = 0; i < 16; i++)
    {
        for (size_t l = 1; l <= 8; l++)
        {
            if (((unifont[(uint32_t)chr][i] >> (8 - l)) & 1UL) == 1)
                *(uint32_t *)target_addr = fcolor;
            else
                *(uint32_t *)target_addr = bcolor;
            target_addr += 4;
        }
        target_addr -= 32;
        target_addr += g_sysgrap.res_x * 4;
    }
}
void kputwchar(uint32_t x,uint32_t y,wchar_t wchr,uint32_t fcolor,uint32_t bcolor) //Exp
{
    if (wchr == 0x00)
        wchr = L' ';   
    addr_t * target_addr = (void *)(g_sysgrap.base_addr + (y*g_sysgrap.res_x*32*2 + x*32));
    for (size_t i = 0; i < 32; i+=2)
    {
        for (size_t l = 1; l <=16; l++)
        {
            if  (((uint16_t)((uint16_t)unifont[wchr][i]<<8)+unifont[wchr][i+1] >> (16-l) )& 1UL)
                *(uint32_t *)target_addr = fcolor;
            else
                *(uint32_t *)target_addr = bcolor;
            target_addr += 4;
        
        }
        target_addr -=64 ;
        target_addr += g_sysgrap.res_x*4;
    }
    
}
void kputstr(uint32_t x, uint32_t y, char *chr, uint32_t fcolor, uint32_t bcolor)
{
    uint32_t lr = y;
    for (size_t i = 0; *chr != '\0'; i++)
    {
        switch (*chr)
        {
        case '\n':
            lr++;
            break;
        default:
            kputchar(x + i, lr, *chr, fcolor, bcolor);
            break;
        }
        chr++;
    }
}
void kputwstr(uint32_t x, uint32_t y, wchar_t *chr, uint32_t fcolor, uint32_t bcolor)
{
    uint32_t lr = y;
    for (size_t i = 0; *chr != 0; i++)
    {
        switch (*chr)
        {
        case '\n':
            lr++;
            break;
        default:
            if (*chr < 128 && *chr > 32)
            {
                kputchar(x, lr, *chr, fcolor, bcolor);
                x += 2;
            }
            else
            {
                kputwchar(x, lr, *chr, fcolor, bcolor);
                x += 1;
            }
            break;
        }
        chr++;
    }
}
void kputwstrc(uint32_t x, uint32_t y, wchar_t *chr, uint32_t fcolor, uint32_t bcolor, uint32_t l)
{
    uint32_t lr = y;
    for (size_t i = 0; i < l; i++)
    {
        switch (*chr)
        {
        case '\n':
            lr++;
            break;
        default:
            kputwchar(x + 2*i, lr, *chr, fcolor, bcolor);
            break;
        }
        chr++;
    }
}
void kputstrc(uint32_t x, uint32_t y, char *chr, uint32_t fcolor, uint32_t bcolor, uint32_t l)
{
    uint32_t lr = y;
    for (size_t i = 0; i < l; i++)
    {
        switch (*chr)
        {
        case '\n':
            lr++;
            break;
        default:
            kputchar(x + i, lr, *chr, fcolor, bcolor);
            break;
        }
        chr++;
    }
}
void kputnum(uint32_t x, uint32_t y, uint32_t num, uint32_t fcolor, uint32_t bcolor)
{
    char tmp[11] = {"0x????????\0"};
    for (size_t i = 2; i < 10; i++)
    {
        switch (((num >> ((9 - i)) * 4)) & 0xfUL)
        {
        case 0:
            tmp[i] = '0';
            break;
        case 1:
            tmp[i] = '1';
            break;
        case 2:
            tmp[i] = '2';
            break;
        case 3:
            tmp[i] = '3';
            break;
        case 4:
            tmp[i] = '4';
            break;
        case 5:
            tmp[i] = '5';
            break;
        case 6:
            tmp[i] = '6';
            break;
        case 7:
            tmp[i] = '7';
            break;
        case 8:
            tmp[i] = '8';
            break;
        case 9:
            tmp[i] = '9';
            break;
        case 10:
            tmp[i] = 'A';
            break;
        case 11:
            tmp[i] = 'B';
            break;
        case 12:
            tmp[i] = 'C';
            break;
        case 13:
            tmp[i] = 'D';
            break;
        case 14:
            tmp[i] = 'E';
            break;
        case 15:
            tmp[i] = 'F';
            break;
        default:
            tmp[i] = '*';
            break;
        }
    }
    kputstr(x, y, tmp, fcolor, bcolor);
}