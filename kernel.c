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
#include <multiboot.h>
#include <types.h>
#include <ioport.h>
#include <sysop.h>
#include <video.h>
int kmain(addr_t* g_kinfo)
{
    if (get_reg_rax() != MBT_AFL_MAGIC) //Do not loaded from Multiboot2 loader
    {
        while (1)
            hlt_cpu();
    }
    const struct mbt_afl_header *p_mbti = (void *)get_reg_rbx;
    char *p_ldr_name;
    int des_alf = (p_mbti->total_size - 8);
    struct mbt_afl_stdhdr *p_nfub = (struct mbt_afl_stdhdr *)p_mbti;
    while (des_alf > 0)
    {
        switch (p_nfub->type)
        {
        case MBT_AFL_VBE_TYPE:

            init_vbe(((struct mbt_afi_vbe *)p_nfub)->vbe_contol_info, ((struct mbt_afi_vbe *)p_nfub)->vbe_mode_info);

            des_alf -= p_nfub->size;
            p_nfub = ((char *)p_nfub + p_nfub->size);
            break;
        case MBT_AFL_BLDN_TYPE:
            *p_ldr_name = &(((struct mbt_afi_blname *)p_nfub)->string);
            des_alf -= p_nfub->size;
            p_nfub = ((char *)p_nfub + p_nfub->size);
            break;
        default:
            des_alf -= p_nfub->size;
            p_nfub = ((char *)p_nfub + p_nfub->size);
            break;
        }
    }
    test_video();
    while (1)
    {
    }
    hlt_cpu();
}