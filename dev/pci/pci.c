/*
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
/*Copyright (C) 2020-2021 AlanCui*/
#include <kfrme.h>
#include <io/port.h>
#include <console/video.h>
#include "pci.h"
pci_device g_pcidev[512];
uint32_t dev_ptr = 0;
uint8_t pci_read_configb(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t ldev = (uint32_t)dev;
    uint32_t lfunc = (uint32_t)func;
    address = (uint32_t)((lbus << 16) | (ldev << 11) |  (lfunc << 8) | (offset & 0xfc) | ((uint32_t)1 << 31));
    out_port32(0xcf8, address);
    return (uint8_t)in_port32(0xcfc)&(0xff << ((offset && 0xff)*8));
}
uint16_t pci_read_configw(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t ldev = (uint32_t)dev;
    uint32_t lfunc = (uint32_t)func;
    address = (uint32_t)((lbus << 16) | (ldev << 11) |  (lfunc << 8) | (offset & 0xfc) | ((uint32_t)1 << 31));
    out_port32(0xcf8, address);
    return (uint16_t)((in_port32(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
}
uint32_t pci_read_configd(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t ldev = (uint32_t)dev;
    uint32_t lfunc = (uint32_t)func;
    address = (uint32_t)((lbus << 16) | (ldev << 11) |  (lfunc << 8) | (offset & 0xfc) | ((uint32_t)1 << 31));
    out_port32(0xcf8, address);
    return in_port32(0xcfc);
}
void init_pci(void)
{
    klog("pci","scanning device...");
    
    for (size_t i = 0; i < 16; i++)
    {
        for (size_t l = 0; l < 128; l++)
        {
                if(pci_read_configd(i,l,0,0) != 0xffffffff)
                {
                    pci_dectdev(i,l,0);
                }
        }
    }
    klog("pci","OK");
}
void pci_scan_bus(uint8_t bus, uint8_t dev)
{
        for (size_t l = 1; l < 128; l++)
        {
            if(pci_read_configd(bus,dev,l,0) != 0xffffffff)
            {
                pci_dectdev(bus,dev,l);
            }
            
        }
}
void pci_dectdev(uint8_t bus, uint8_t dev, uint8_t func)
{
    pci_device tmp;
    tmp.bus = bus;
    tmp.dev =dev;
    tmp.func = func;
    tmp.id = pci_read_configd(bus,dev,func,0);
    char ip[128] = {0};
    char ty[128] = {0};
    char ifn[128] = {0};
    uint32_t need_scan =0;
               for (size_t i = 0; i < dev_ptr; i++)
                if(g_pcidev[i].id == pci_read_configd(bus,dev,func,0))
                    return;
    klog("pci","found device at Bus.%w Dev.%w Func.%w ID:%h Type:%h",bus,dev,func,pci_read_configd(bus,dev,func,0),pci_read_configd(bus,dev,func,8));
   switch((pci_read_configd(bus,dev,func,8) & 0xff000000 )>> 24)
   {
       case 0x01://Mass Storage Controller 
           strcpy(ip,"Mass Storage Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: //SCSI Bus Controller
                strcpy(ty,"SCSI Bus Controller");
                tmp.type = SCSI_MSC;
                break;
            case 0x01: //IDE Controller
                strcpy(ty,"IDE Controller");
                tmp.type = IDE_MSC;
                break;
            case 0x02: //Floppy Disk Controller
                strcpy(ty,"Floppy Disk Controller");
                tmp.type = FD_MSC;
                break;
            case 0x03: //IPI Bus Controller
                strcpy(ty,"IPI Bus Controller");
                tmp.type = IPI_MSC;
                break;
            case 0x04: //RAID Controller
                strcpy(ty,"RAID Controller");
                tmp.type = RAID_MSC;
                break;
            case 0x05: //ATA Controller
                strcpy(ty,"ATA Controller");
                tmp.type = ATA_MSC;
                break;
            case 0x06: //Serial ATA 
                strcpy(ty,"Serial ATA-");
                switch ((pci_read_configd(bus,dev,func,8) & 0x0000ff00)>>8)
                {
                case 0x01://AHCI
                    strcpy(ifn,"AHCI");
                    tmp.type = SATA_MSC;
                    break;
                case 0x02://Serial Storage Bus
                    if(func ==0){
                    tmp.type = SATA_B;
                    g_pcidev[dev_ptr++] = tmp;
                    klog("pci","----------Storage Bus(SATA)----------");
                    pci_scan_bus(bus,dev);
                    klog("pci","----------+++++++++++++++++----------");
                    strcpy(ifn,"Serial Storage Bus");
                    need_scan = 1;
                }
                    break;
                default: // Other
                    strcpy(ifn,"Other");
                    break;
                }
                break;
            case 0x07: //Serial Attached SCSI
                strcpy(ty,"Serial Attached SCSI-");
                switch ((pci_read_configd(bus,dev,func,8) & 0x0000ff00)>>8)
                {
                case 0x00://AHCI
                    strcpy(ifn,"SAS");
                    tmp.type = SAS_MSC;
                    break;
                case 0x01://Serial Storage Bus
                    if(func ==0){
                    tmp.type = SAS_B;
                    g_pcidev[dev_ptr++] = tmp;
                    klog("pci","----------Storage Bus(SAS)----------");
                    pci_scan_bus(bus,dev);
                    klog("pci","----------++++++++++++++++----------");
                    strcpy(ifn,"Serial Storage Bus");
                    need_scan = 1;
                }
                    break;
                }
                break;
            case 0x08: //Non-Volatile Memory Controller
                strcpy(ty,"Non-Volatile Memory Controller");
                tmp.type = NVMC_MSC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_MSC;
                break;
            }
            break;
        case 0x02://Network Controller
           strcpy(ip,"Network Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: //Ethernet Controller
                strcpy(ty,"Ethernet Controller");
                tmp.type = ETH_NC;
                break;
            case 0x01: //Token Ring Controller
                strcpy(ty,"Token Ring Controller");
                tmp.type = TR_NC;
                break;
            case 0x02: //FDDI Controller
                strcpy(ty,"FDDI Controller");
                tmp.type = FDDI_NC;
                break;
            case 0x03: //ATM Controller
                strcpy(ty,"ATM Controller");
                tmp.type = ATM_NC;
                break;
            case 0x04: //ISDN Controller
                strcpy(ty,"ISDN Controller");
                tmp.type = ISDN_NC;
                break;
            case 0x05: //WorldFip Controller
                strcpy(ty,"WorldFip Controller");
                tmp.type = WF_NC;
                break;
            case 0x06: //PICMG 2.14 Multi Computing
                strcpy(ty,"PICMG 2.14 Multi Computing");
                tmp.type = PICMG_NC;
                break;
            case 0x07: //Infiniband Controller
                strcpy(ty,"Infiniband Controller");
                tmp.type = IF_NC;
                break;
            case 0x08: //Fabric Controller
                strcpy(ty,"Ethernet Controller");
                tmp.type = FB_NC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_NC;
                break;
            }
            break;
        case 0x03://Display Controller
           strcpy(ip,"Display Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: //VGA Compatible Controller
                strcpy(ty,"VGA Compatible Controller");
                tmp.type = VGA_VC;
                break;
            case 0x01: //XGA Controller
                strcpy(ty,"XGA Controller");
                tmp.type = XGA_VC;
                break;
            case 0x02: //3D Controller
                strcpy(ty,"3D Controller");
                tmp.type = TD_VC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_VC;
                break;
            }
            break;
        case 0x04://Multimedia Controller
           strcpy(ip,"Multimedia Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: //Multimedia Video Controller
                strcpy(ty,"Multimedia Video Controller");
                tmp.type = MVD_MMC;
                break;
            case 0x01: //Multimedia Audio Controller
                strcpy(ty,"Multimedia Audio Controller");
                tmp.type = MAU_MMC;
                break;
            case 0x02: //Computer Telephony Device
                strcpy(ty,"Computer Telephony Device");
                tmp.type = CT_MMC;
                break;
            case 0x03: //Audio Device
                strcpy(ty,"Audio Device");
                tmp.type = AU_MMC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_MMC;
                break;
            }
            break;
        case 0x05://Memory Controller
           strcpy(ip,"Memory Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: //RAM Controller
                strcpy(ty,"RAM Controller");
                tmp.type = RAM_MC;
                break;
            case 0x01: //Flash Controller
                strcpy(ty,"Flash Controller");
                tmp.type = FL_MC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_MC;
                break;
            }
            break;
        case 0x06://Bridge Device
           strcpy(ip,"Bridge Device-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: //Host Bridge
                strcpy(ty,"Host Bridge");
                tmp.type = HOST_B;
                break;
            case 0x01: //ISA Bridge
                if(func ==0){
                    tmp.type = ISA_B;
                    g_pcidev[dev_ptr++] = tmp;
                    klog("pci","----------ISA Bridge----------");
                    pci_scan_bus(bus,dev);
                    klog("pci","----------++++++++++----------");
                    strcpy(ty,"ISA Bridge");
                    need_scan = 1;
                }
                break;
           case 0x02: //EISA Bridge
                strcpy(ty,"EISA Bridge");
                tmp.type = EISA_B;
                break;
            case 0x03: //MCA Bridge
                strcpy(ty,"MCA Bridge");
                tmp.type = MCA_B;
                break;
            case 0x04: //PCI-to-PCI Bridge
                strcpy(ty,"PCI-to-PCI Bridge");
                tmp.type = P2P_B;
                break;
            case 0x05: //PCMCIA Bridge
                strcpy(ty,"PCMCIA Bridge");
                tmp.type = PCMCIA_B;
                break;
            case 0x06: //NuBus Bridge
                strcpy(ty,"NuBus Bridge");
                tmp.type = NUS_B;
                break;
            case 0x07: //CardBus Bridge
                strcpy(ty,"CardBus Bridgee");
                tmp.type = CBS_B;
                break;
            case 0x08: //RACEway Bridge
                strcpy(ty,"RACEway Bridge");
                tmp.type = RABS_B;
            case 0x09: //PCI-to-PCI Bridge
                strcpy(ty,"PCI-to-PCI Bridge");
                tmp.type = P2PC_B;
            case 0x0A: // InfiniBand-to-PCI Host Bridge
                strcpy(ty,"InfiniBand-to-PCI Host Bridge");
                tmp.type = IB2P_B;
                break;
            
            default:
            case 0x80: //Other
                strcpy(ty,"Other");
                need_scan =0;
                tmp.type = OTH_B;
                break;
            }
            break;
        case 0x07://Simple Communication Controller
           strcpy(ip,"Simple Communication Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: // Serial Controller
                strcpy(ty," Serial Controller");
                tmp.type = SC_SCC;
                break;
            case 0x01: //Parallel Controller
                strcpy(ty,"Parallel Controller");
                tmp.type = PC_SCC;
                break;
            case 0x02: //Multiport Serial Controller
                strcpy(ty,"Multiport Serial Controller");
                tmp.type = MS_SCC;
                break;
            case 0x03: //Modem
                strcpy(ty,"Modem");
                tmp.type = MD_SCC;
                break;
            case 0x04: //IEEE 488.1/2 (GPIB) Controller
                strcpy(ty,"IEEE 488.1/2 (GPIB) Controller");
                tmp.type = GPIB_SCC;
                break;
            case 0x05: //Smart Card
                strcpy(ty,"Smart Card");
                tmp.type = SCD_SCC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_SCC;
                break;
            }
            break;
        case 0x0c://Serial Bus Controller
           strcpy(ip,"Serial Bus Controller-");
            switch ((pci_read_configd(bus,dev,func,8) & 0x00ff0000)>>16)
            {
            case 0x00: // FireWire (IEEE 1394) Controller
                strcpy(ty,"FireWire (IEEE 1394) Controller");
                tmp.type = FW_SBC;
                break;
            case 0x01: //ACCESS Bus
                strcpy(ty,"ACCESS Bus");
                tmp.type = ACE_SBC;
                break;
            case 0x02: //SSA
                strcpy(ty,"SSA");
                tmp.type = SSA_SBC;
                break;
            case 0x03: //USB Controller / Device
                strcpy(ty,"USB Controller-");
                switch ((pci_read_configd(bus,dev,func,8) & 0x0000ff00)>>8)
                {
                case 0x00:
                    strcpy(ifn,"UHCI Controller");
                    tmp.type = UHCI_B;
                    goto usb_bus;
                case 0x10:
                    strcpy(ifn,"OHCI Controller");
                    tmp.type = OHCI_B;
                    goto usb_bus;
                case 0x20:
                    strcpy(ifn,"EHCI (USB2) Controller");
                    tmp.type = EHCI_B;
                    goto usb_bus;
                case 0x30:
                    strcpy(ifn,"XHCI (USB3) Controller");
                    tmp.type = XHCI_B;
                usb_bus:
                    break;
                case 0xfe:
                    tmp.type = USB_SBC;
                    strcpy(ifn,"USB Device");
                default:
                    tmp.type = USB_OTH;
                    break;
                }
                break;
            case 0x04: //Fibre Channel	
                strcpy(ty,"Fibre Channel");
                tmp.type = FC_SBC;
                break;
            case 0x05: //SMBus
                strcpy(ty,"SMBus");
                tmp.type = SMB_SBC;
                break;
            case 0x06: //InfiniBand
                strcpy(ty,"InfiniBand");
                tmp.type = IB_SBC;
                break;
            case 0x07: //IPMI Interface
                strcpy(ty,"IPMI Interface");
                tmp.type = IPMI_SBC;
                break;
            case 0x80: //Other
                strcpy(ty,"Other");
                tmp.type = OTH_SBC;
                break;
            }
            break;
            
   }
   if(need_scan != 1)
    g_pcidev[dev_ptr++] = tmp;
    klog("pci",strcat(strcat(ip,ty),ifn),bus,dev,func);
}