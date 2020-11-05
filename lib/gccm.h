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
#ifndef _GCCM_H_
#define _GCCM_H_
//Complie object into a Fixed section
#define IN_SECTION(scname) \
    __attribute__((section(scname)))
//Complie struct without any align
#define SRT_PACKED __attribute__((__packed__))
//Complie without any optimization
#define ASM_DNO __volatile__
#endif