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
#ifndef _PCI_H_
#define _PCI_H_
#define HOST_B 1
#define ISA_B 2
#define OTH_B 3
#define VGA_VC 4
#define OTH_VC 5
#define ETH_NC 6
#define OTH_NC 7
#define SCSI_MSC 8
#define IDE_MSC 9
#define EISA_B 10
#define MCA_B 11
#define P2P_B 12
#define PCMCIA_B 13
#define NUS_B 14
#define CBS_B 15
#define RABS_B 16
#define P2PC_B 17
#define IB2P_B 18
#define SATA_B 19
#define FD_MSC 20
#define OTH_MSC 21
#define IPI_MSC 22
#define ATA_MSC 23
#define SATA_B 24
#define SATA_MSC 25
#define SAS_MSC 26
#define SAS_B 27
#define NVMC_MSC 28
#define OTH_MSC 29
#define RAID_MSC 30
#define TR_NC 31
#define FDDI_NC 32
#define ATM_NC 33
#define ISDN_NC 34
#define WF_NC 35
#define PICMG_NC 36
#define IF_NC 37
#define FB_NC 38
#define XGA_VC 39
#define TD_VC 40
#define MVD_MMC 41
#define MAU_MMC 42
#define CT_MMC 43
#define AU_MMC 44
#define OTH_MMC 45
#define RAM_MC 46
#define FL_MC 47
#define OTH_MC 48
#define SC_SCC 49
#define PC_SCC 50
#define MS_SCC 51
#define MD_SCC 52
#define GPIB_SCC 53
#define SCD_SCC 54
#define OTH_SCC 55
#define FW_SBC 56
#define ACE_SBC 57
#define SSA_SBC 58
#define UHCI_B 59
#define OHCI_B 60
#define EHCI_B 61
#define XHCI_B 62
#define USB_SBC 63
#define USB_OTH 64
#define FC_SBC 65
#define SMB_SBC 66
#define IB_SBC 67
#define IPMI_SBC 68
#define OTH_SBC 69
 typedef struct 
{
    uint32_t bus,dev,func,id;
    uint32_t type;
}pci_device;

#endif