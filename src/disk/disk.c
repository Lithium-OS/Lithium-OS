#include "../lib/type.h"
#include "../device/port.h"

// LBA48 读磁盘扇区加载到指定地址
uint32_t read_disk_sector(uint16_t high_sec, uint32_t low_sec, uint16_t sec_num,
    uint32_t* target_ptr)
{
    uint8_t i = 0;
    while (i=1)
        i = ((in_port8(0x1f7)<< 4) >> 7);
    out_port8(0x01f1,0x0000);
    out_port8(0x01f1,0x0000);
    out_port8(0x01f2,(sec_num >> 8)); //high 8
    out_port8(0x01f2,((sec_num << 8) >> 8)); //low 8
    out_port8(0x01f3,(low_sec >> 24)); //b24-31
    out_port8(0x01f3,((low_sec << 24) >> 24)); //b0-7
    out_port8(0x01f4,(high_sec << 8) >> 8); //b32-39
    out_port8(0x01f4,(((low_sec >> 8) << 24) >> 24)); //b8-15
    out_port8(0x01f5,(high_sec >> 8)); //b40-47
    out_port8(0x01f5,(((low_sec >> 16) << 24) >> 24)); //b16-23
    out_port8(0x01f6,0b01000000); //MasterDsk
    out_port8(0x01f7,0x24); //Read

    for (uint32_t i = 0; i < sec_num * 256; i++)
    {
        *target_ptr = in_port16(0x01f0);
        target_ptr + 2;
    }
    
    return get_err();
}

static uint32_t get_err(void)
{
    if((in_port8(0x1f7)<< 7) >> 7)
        return in_port8(0x1f1);
    else
        return 0;
}
