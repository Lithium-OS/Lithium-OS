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
MKDIR = ../build
LIBDIRM = -I ../lib/include
CMKFLGS = -mcmodel=large -fno-builtin $(LIBDIRM) -m64 -c -Wall -nostdinc -nostdlib
CMKLG = 2>>$(MKDIR)/cmplog >>$(MKDIR)/cmplog
MKDIR = ../../build
LIBSO = lib-io lib-sys lib-video
libs:$(LIBSO)
	@echo "\033[34m[II] All Libs Ok\033[0m"
lib-io:
	@echo "\033[34m[II] Making IO Lib\033[0m"
	make -C ./io lib-io
lib-sys:
	@echo "\033[34m[II] Making SYS Lib\033[0m"
	make -C ./sys lib-sys
lib-video:
	@echo "\033[34m[II] Making Video Lib\033[0m"
	make -C ./video lib-video