/*
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
    along with this program.  If not, see <https:enses/>.
*/
/*Copyright (C) 2020-2021 AlanCui*/
#include <kfrme.h>
#include <io/port.h>
#include <console/video.h>
#include <console/tty.h>
#define    FIS_REG_H2D    0x27
#define    FIS_REG_D2H    0x34
#define    FIS_DMA_ACT    0x39
#define    FIS_DMA_SETUP    0x41
#define    FIS_DATA    0x46
#define    FIS_BIST    0x58
#define    FIS_PIO_SETUP    0x5F
#define    FIS_DEV_BITS    0xA1
typedef struct
{
    uint8_t  type;  
    uint8_t  pctl;
    uint8_t  cmd;    
    uint8_t  feal;
    uint8_t  lba0;
    uint8_t  lba1;
    uint8_t  lba2;
    uint8_t  device;
    uint8_t  lba3;
    uint8_t  lba4;
    uint8_t  lba5; 
    uint8_t  feah;  
    uint16_t  cnt;
    uint8_t  icc;  
    uint8_t  control;  
    uint8_t  rev[4];  
} ahci_fis_rh2d;
typedef struct
{
    uint8_t  type;  
    uint8_t  pctl;
    uint8_t  cmd;    
    uint8_t  status;
    uint8_t  err;
    uint8_t  lba0;
    uint8_t  lba1;
    uint8_t  lba2;
    uint8_t  dev;
    uint8_t  lba3;
    uint8_t  lba4;
    uint8_t  lba5; 
    uint8_t  rev0;  
    uint16_t  cnt;
    uint8_t  rev1;  
    uint8_t  rev2[4];  
} ahci_fis_rd2h;
typedef struct 
{
    uint32_t c_addr;
    uint32_t c_up;
    uint32_t fis_addr;
    uint32_t fis_up;
    uint32_t intr_stat;
    uint32_t intr_en; 
    uint32_t cmd;
    uint32_t rev0;    
    uint32_t tfd;
    uint32_t sig;
    uint32_t stat;
    uint32_t ctl;
    uint32_t aerr;
    uint32_t active;
    uint32_t issue;
    uint32_t noti;
    uint32_t fis_sctl;   
    uint32_t rev1[11];
    uint32_t vendor[4];
}__attribute__(__volatile__) ahci_port;
typedef struct 
{
    uint32_t cap;   
    uint32_t ghctrl;       
    uint32_t intr;    
    uint32_t port;    
    uint32_t ver;    
    uint32_t ctl;
    uint32_t pts;
    uint32_t loc;
    uint32_t ectl;
    uint32_t cap2;
    uint32_t bohc;
    uint8_t  rev[0xa0-0x2C];
    uint8_t  vendor[0x100-0xa0];
    ahci_port cfp[32];   
}__attribute__(__volatile__) ahci_abar;