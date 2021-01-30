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

lib-video:$(MKDIR)/vbe.o $(MKDIR)/univideo.o $(MKDIR)/unifont.o $(MKDIR)/klog.o
$(MKDIR)/vbe.o:vbe.c
	$(CC) $(CMKFLGS) vbe.c -o $(MKDIR)/vbe.o $(CMKLG)
$(MKDIR)/univideo.o:univideo.c
	$(CC) $(CMKFLGS) univideo.c -o $(MKDIR)/univideo.o $(CMKLG)
$(MKDIR)/unifont.o:unifont.hex
	$(CC) $(CMKFLGS) unifont.hex -o $(MKDIR)/unifont.o $(CMKLG)
$(MKDIR)/klog.o:klog.c
	$(CC) $(CMKFLGS) klog.c -o $(MKDIR)/klog.o $(CMKLG)