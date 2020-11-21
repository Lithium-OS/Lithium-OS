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

//Still NOT support all afl blocks --AlanCui 2020/10/23
#pragma once
#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_
#include <types.h>
//Define MultiBoot version
#define MBT_VERSION 2
#if MBT_VERSION == 2
//The type num of end_tag
#define MBT_END_TYPE 0
//The type num of video_frame_buffer_tag
#define MBT_VBUF_TYPE 5
//The type num of elf64_tag
#define MBT_ELF64_TYPE 9
//The type num of reloca_tag
#define MBT_RELOCT_TYPE 10
//The address of Kernel(PERF)
#define MBT_LDPHT_ADDR 0x100000
//Magic Num
#define MBT_LDR_MAGIC 0xe85250d6
//Magic Num
#define MBT_AFL_MAGIC 0x36d76289
//The type num of Afl VBEblock
#define MBT_AFL_VBE_TYPE 7
//The type num of Afl Bootloader name
#define MBT_AFL_BLDN_TYPE 2
//ArchNum
#define MBT_ARCH_i386 0

/*Needs To Config*/
#define MBT_NOW_ARCH 0
/*****************/
// Std infoblock header provided by BootLoader
struct mbt_afl_header
{
    uint32_t total_size;
    uint32_t rev;
} __attribute__((__packed__));
// Stdheader of funcblock provided by BootLoader
struct mbt_afl_stdhdr
{
    // type of this block
    uint32_t type;
    // size of this block (byte)
    uint32_t size;
} __attribute__((__packed__));
// Basic memory infomation provided by BootLoader
struct mbt_afl_bmi
{
    struct mbt_afl_stdhdr header;
    // the lowest memory address that can be accessed safely
    uint32_t mem_lower;
    // the highest memory address that can be accessed safely
    uint32_t mem_upper;
} __attribute__((__packed__));
// BIOS boot device infomation provided by BootLoader
struct mbt_afl_bd
{
    struct mbt_afl_stdhdr header;
    // number of boot device
    uint32_t biosdev;
    // number of boot partition
    uint32_t partition;
    // number of boot subpartition
    uint32_t sub_partition;
} __attribute__((__packed__));
// Boot command line provided by BootLoader
struct mbt_afi_cmd
{
    struct mbt_afl_stdhdr header;
    // commandline [Caution! string member is varies]
    uint8_t string;
} __attribute__((__packed__));
// Modules infomation provided by BootLoader
struct mbt_afi_mods
{
    struct mbt_afl_stdhdr header;
    // start address of modules
    uint32_t mod_start;
    // end address of modules
    uint32_t mod_end;
    // mods [Caution! string member is varies]
    uint8_t string;
} __attribute__((__packed__));
// ELFsym provided by BootLoader [Caution! section headers is varies]
struct mbt_afi_ELFsym
{
    struct mbt_afl_stdhdr header;
    // no description
    uint16_t num;
    // no description
    uint16_t ent_size;
    // no description
    uint16_t shndx;
    // no description
    uint16_t rev;

} __attribute__((__packed__));
// Memory mapping infomation provided by BootLoader [Caution! memorydes(mbt_metr) is varies]
struct mbt_afi_mmap
{
    struct mbt_afl_stdhdr header;
    // size of EACH entry
    uint32_t entry_size;
    // version of entries
    uint32_t entry_version;
} __attribute__((__packed__));
struct mbt_metr
{
    // base address of this memory section
    uint64_t base_addr;
    // length of this memory section
    uint64_t length;
    // type of this memory section
    uint32_t type;
    uint32_t rev;
} __attribute__((__packed__));
// Bootloader name provided by BootLoader
struct mbt_afi_blname
{
    struct mbt_afl_stdhdr header;
    // name [Caution! string member is varies]
    uint8_t string;
} __attribute__((__packed__));
// APM table provided by BootLoader
struct mbt_afi_apmt
{
    struct mbt_afl_stdhdr header;
    // see Advanced power managenment (APM) BIOS Interface Specification for more infomation
    uint16_t version, cseg;
    // see Advanced power managenment (APM) BIOS Interface Specification for more infomation
    uint32_t offset;
    // see Advanced power managenment (APM) BIOS Interface Specification for more infomation
    uint16_t cseg_16, dseg, flags, cseg_len, cseg_16_len, dseg_len;
} __attribute__((__packed__));
// VBE info provided by BootLoader
struct mbt_afi_vbe
{
    struct mbt_afl_stdhdr header;
    // vbemode (see VESA BIOS Expand for more infomation)
    uint16_t vbe_mode;
    // vbe protect mode interface seg(see VESA BIOS Expand for more infomation)
    uint16_t vbe_inter_seg;
    // vbe protect mode interface offset(see VESA BIOS Expand for more infomation)
    uint16_t vbe_inter_off;
    // vbe protect mode interface length(see VESA BIOS Expand for more infomation)
    uint16_t vbe_inter_len;
    // vbe info block(see VESA BIOS Expand for more infomation)
    uint8_t vbe_contol_info[512];
    // vbe video mode info block(see VESA BIOS Expand for more infomation)
    uint8_t vbe_mode_info[256];
} __attribute__((__packed__));
// Video framebuffer infomation provided by BootLoader [Caution! color_info member is varies]
struct mbt_afl_vbuf
{
    struct mbt_afl_stdhdr header;
    // vbuf base address(see VESA BIOS Expand for more infomation)
    uint64_t addr;
    // vbuf pixel infomation attr(see VESA BIOS Expand for more infomation)
    uint32_t pit, width, height;
    // vbuf pixel infomation attr(see VESA BIOS Expand for more infomation)
    uint8_t bpp, type, rev;
} __attribute__((__packed__));
// ELF 32/64bit system table provided by BootLoader
struct mbt_afl_elf_syst
{
    struct mbt_afl_stdhdr header;
    uint64_t *ptr;
} __attribute__((__packed__));

#if 0
struct mbt_header
{
    const uint32_t magic;
    const uint32_t arch;
    const uint32_t h_len;
    const uint32_t h_chksum;
};

struct mbt_elf_64
{
    const uint16_t num;
     type;
    uint16_t num;
     flags;
    const uint32_t size;
};
struct mbt_vbuf
{
    const uint16_t num;
     type;
    uint16_t num;
     flags;
    const uint32_t size;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};
struct mbt_reloct
{
    const uint16_t num;
     type;
    uint16_t num;
     flags;
    const uint32_t size;
    uint32_t min_addr;
    uint32_t max_addr;
    uint32_t align;
    uint32_t perf;
};
struct mbt_endtag
{
    const uint16_t num;
     type;
    const uint16_t num;
     flags;
    const uint32_t size;
};
#endif
#else
#error NOT SUPPORT MBT_VERSION
#endif
#endif