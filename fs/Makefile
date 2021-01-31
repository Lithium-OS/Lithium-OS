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
lib-fs:$(MKDIR)/vfs.o $(MKDIR)/vfstring.o
fs-lifsrd:
	make -C ./lifsrd lifsrd
$(MKDIR)/vfs.o:vfs.c
	$(CC) $(CMKFLGS) vfs.c -o $(MKDIR)/vfs.o $(CMKLG)
$(MKDIR)/vfstring.o:vfstring.c
	$(CC) $(CMKFLGS) vfstring.c -o $(MKDIR)/vfstring.o $(CMKLG)