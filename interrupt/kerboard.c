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
#include <ioport.h>
#include <video.h>
uint8_t kb_buf[512]={0xff};
uint8_t * kbb_p = &(kb_buf[511]);
uint32_t lctrl = 0;
uint32_t lalt = 0;
uint32_t backspace = 0;
void als_keyborad_code()
{
       switch (*kbb_p)
       {
        case 0x1d://Left ctrl MAKE
            lctrl =1;
           break;
        case 0x9d://Left ctrl BREAK
            lctrl =0;
            break;
        case 0x38://Left alt MAKE
            lalt =1;
           break;
        case 0xb8://Left alt BREAK
            lalt =0;
           break;
        case 0x0e://Backspace MAKE
            backspace =1;
           break;
        case 0x8e://Backspace BREAK
            backspace =0;
           break;
       default:
           break;
       }
    if (kbb_p != &(kb_buf[511]))
        kbb_p++;
    if (lctrl ==1 && lalt == 1 && backspace == 1)
    {
        out_port8(0x64,0xfe);
    }
    
}