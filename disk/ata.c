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
const uint16_t ata_port_master[9] = {0x1f0, 0x1f1, 0x1f2, 0x1f3, 0x1f4, 0x1f5, 0x1f6, 0x1f7, 0b010000};
void ata_wait(uint8_t *ata)
{
    while ((in_port8(ata[7]) >> 6) == 1)
        ;
}
sint32_t ata_read_sector(uint8_t *ata, uint64_t lba, void *addr)
{
    if ((lba) > 0xFFFFFFFFFFFF)
        return -1;
    ata_wait(ata);
    out_port8(ata[1], 0);
    out_port8(ata[2], 0);
    out_port8(ata[3], (lba << 16) >> 40);
    out_port8(ata[4], (lba << 8) >> 40);
    out_port8(ata[5], (lba << 0) >> 40);
    out_port8(ata[1], 0);
    out_port8(ata[2], 1);
    out_port8(ata[3], (lba << 40) >> 40);
    out_port8(ata[4], (lba << 32) >> 40);
    out_port8(ata[5], (lba << 24) >> 40);
    out_port8(ata[6], ata[8]);
    ata_wait(ata);
    out_port8(ata[7], 0x24);
    ata_wait(ata);
    void *p = (void *)addr;
    while ((in_port8(ata[7]) << 4) >> 7 == 1)
    {
        *(uint16_t *)p = in_port16(ata[1]);
        p += 2;
    }
    return 0;
}
sint32_t ata_write_sector(uint8_t *ata, void *addr, uint64_t lba)
{
    if ((lba) > 0xFFFFFFFFFFFF)
        return -1;
    ata_wait(ata);
    out_port8(ata[1], 0);
    out_port8(ata[2], 0);
    out_port8(ata[3], (lba << 16) >> 40);
    out_port8(ata[4], (lba << 8) >> 40);
    out_port8(ata[5], (lba << 0) >> 40);
    out_port8(ata[1], 0);
    out_port8(ata[2], 1);
    out_port8(ata[3], (lba << 40) >> 40);
    out_port8(ata[4], (lba << 32) >> 40);
    out_port8(ata[5], (lba << 24) >> 40);
    out_port8(ata[6], ata[8]);
    ata_wait(ata);
    out_port8(ata[7], 0x34);
    ata_wait(ata);
    void *p = (void *)addr;
    while ((in_port8(ata[7]) << 4) >> 7 == 1)
    {
        out_port16(ata[1], *(uint16_t *)p);
        p += 2;
    }
    return 0;
}