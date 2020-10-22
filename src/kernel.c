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
#include <gccm.h>
    const long IN_SECTION(".mbt2std") k__mtb_header_magic = MBT_LDR_MAGIC ;
    const long IN_SECTION(".mbt2std") k__mtb_header_arch = MBT_NOW_ARCH ;
    const long IN_SECTION(".mbt2std") k__mtb_header_h_len = 16;
    const long IN_SECTION(".mbt2std") k__mtb_header_h_chksum = (unsigned long)(-(MBT_LDR_MAGIC+MBT_NOW_ARCH+16));
    const short IN_SECTION(".mbt2std") k__mtb_elf_type = MBT_ELF64_TYPE;
    const short IN_SECTION(".mbt2std") k__mtb_elf_flags = 0;
    const long IN_SECTION(".mbt2std") k__mtb_elf_size = 8;
    const short IN_SECTION(".mbt2std") k__mtb_vbuf_type = MBT_VBUF_TYPE;
    const short IN_SECTION(".mbt2std") k__mtb_vbuf_flags = 0;
    const long IN_SECTION(".mbt2std") k__mtb_vbuf_size = 20;
    const long IN_SECTION(".mbt2std") k__mtb_vbuf_width = 1024;
    const long IN_SECTION(".mbt2std") k__mtb_vbuf_height = 768;
    const long IN_SECTION(".mbt2std") k__mtb_vbuf_depth = 32;
    const short IN_SECTION(".mbt2std") k__mtb_reloct_type = MBT_RELOCT_TYPE;
    const short IN_SECTION(".mbt2std") k__mtb_reloct_flags = 0;
    const long IN_SECTION(".mbt2std") k__mtb_reloct_size = 24;
    const long IN_SECTION(".mbt2std") k__mtb_reloct_min_addr = 0;
    const long IN_SECTION(".mbt2std") k__mtb_reloct_max_addr = 0xffffffffffffffff;
    const long IN_SECTION(".mbt2std") k__mtb_reloct_align = 4096;
    const long IN_SECTION(".mbt2std") k__mtb_reloct_perf = MBT_LDPHT_ADDR;
    const short IN_SECTION(".mbt2std") k__mtb_endtag_type = MBT_END_TYPE;
    const short IN_SECTION(".mbt2std") k__mtb_endtag_flags = 0;
    const long IN_SECTION(".mbt2std") k__mtb_endtag_size = 8;
int kmain(){
    int test = 1;
    while(1)
        ;
}