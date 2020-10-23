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
LIBDIRM = -I ./lib/include
CMKLG = 2>>$(MKDIR)/cmplog >>$(MKDIR)/cmplog
CMKFLGS = -mcmodel=large -fno-builtin $(LIBDIRM) -m64 -c -Wall -nostdinc -nostdlib
system total:
	make clean
	time make all
	@echo "\033[34m[II] Compile Complete.\033[0m"
	@echo "\033[34m[II] Kernel:$(MKDIR)/lithium.elf\033[0m"
	@echo "\033[0m"
	ls -l $(MKDIR)/lithium.elf
	@echo "\033[34m"
	objdump -f ../build/lithium.elf

all:kernel.o
	@echo "\033[34m[II] Linking\033[0m"
	ld -T kernel.lds -b elf64-x86-64 -o $(MKDIR)/lithium~dirty.o $(MKDIR)/*.o
	@echo "\033[34m[II] Cleaning Other Section\033[0m"
	objcopy -R ".eh_frame" -R ".comment" $(MKDIR)/lithium~dirty.o $(MKDIR)/lithium.elf
clean:
	rm -rf ../build/
	mkdir ../build/
kernel.o:libs $(MKDIR)/kheader.o
	@echo "\033[34m[II] Making Kernel\033[0m"
	$(CC) $(CMKFLGS) kernel.c -o $(MKDIR)/kernel.o $(CMKLG)
	@echo "\033[34m[II] EveryLib is Ok,Start Linking\033[0m"
../build/kheader.o:kheader.s
	@echo "\033[34m[II] Making KernelHeader\033[0m"
	$(GAS) --64 -o $(MKDIR)/kheader.o kheader.s
	@echo "\033[34m[II] Header is OK\033[0m"
libs:
	@echo "\033[34m[II] Making Libs\033[0m"
	make -C ./lib libs
dmp:
	objdump -Ss ../build/lithium.elf