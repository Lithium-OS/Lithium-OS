#* Copyright (C) 2020 LithiumOS-Team
#	 This file is part of the Lithium Kernel.
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Affero General Public License as
#    published by the Free Software Foundation, either version 3 of the
#    License, or (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.#
#
#    You should have received a copy of the GNU Affero General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#*/
CC = gcc
CPP = g++
LD = ld
GAS = as
IAS = nasm
MKDIR = ../../../build
LIBDIRM = -I ../include
CMKFLGS = -mcmodel=large -fno-builtin $(LIBDIRM) -m64 -c -Wall -nostdinc -nostdlib
CMKLG = 2>>$(MKDIR)/cmplog >>$(MKDIR)/cmplog
lib-io:ioport.c
	$(CC) $(CMKFLGS) ioport.c -o $(MKDIR)/ioport.o $(CMKLG)