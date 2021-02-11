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

lib-dev:$(MKDIR)/rtc.o $(MKDIR)/udev.o $(MKDIR)/pit.o $(MKDIR)/pci.o $(MKDIR)/sata.o
$(MKDIR)/rtc.o:rtc.c 
	$(CC) $(CMKFLGS) rtc.c -o $(MKDIR)/rtc.o $(CMKLG)
$(MKDIR)/udev.o:udev.c
	$(CC) $(CMKFLGS) udev.c -o $(MKDIR)/udev.o $(CMKLG)
$(MKDIR)/pit.o:pit.c
	$(CC) $(CMKFLGS) pit.c -o $(MKDIR)/pit.o $(CMKLG)
$(MKDIR)/pci.o:pci/pci.c
	$(CC) $(CMKFLGS) pci/pci.c -O2 -o $(MKDIR)/pci.o $(CMKLG)
$(MKDIR)/sata.o:sata.c
	$(CC) $(CMKFLGS) sata.c -O2 -o $(MKDIR)/sata.o $(CMKLG)

