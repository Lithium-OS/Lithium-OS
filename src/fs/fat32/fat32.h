 /* Copyright (C) 2020 LithiumOS-Team

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
/*MainDevloper: AlanCui*/
#include "../../lib/stdint.h"
typedef struct
{
    uint8_t name[8];
    uint32_t cluster;
    uint32_t sector;
    uint16_t sec_length;
    uint32_t byte_length;
} fat32_file_packet;

typedef struct
{
    uint8_t name[8];
    uint8_t exname[3];
    uint8_t attr;
    uint8_t rev;
    uint8_t t_create_ms;
    uint16_t t_create_time;
    uint16_t t_create_date;
    uint16_t t_acc_date;
    uint16_t clu_h;
    uint16_t t_write_time;
    uint16_t t_write_date;
    uint16_t clu_l;
    uint32_t size;
} fat32_file_table;
