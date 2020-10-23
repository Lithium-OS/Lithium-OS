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
#include <sys/types.h>
#ifndef _IOPORT_H_
#define _IOPORT_H_
//Get a word data from port
extern uint16_t in_port16(uint16_t port);
//Get a byte data from port
extern uint8_t in_port8(uint16_t port);
//Output a word data to port
extern void out_port16(uint16_t port, uint16_t valve);
//Output a byte data to port
extern void out_port8(uint16_t port, uint8_t valve);
#endif