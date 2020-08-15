read_disk_sector(u16 high_sec,u32 low_sec,u16 sec_num,u32* target_ptr)
{
    out_port8(0x01f1,0x0000)
    out_port8(0x01f1,0x0000)
    out_port8(0x01f2,(sec_num >> 8)) //high 8
    out_port8(0x01f2,((sec_num << 8) >> 8)) //low 8
    out_port8(0x01f3,(low_sec >> 24)) //b24-31
    out_port8(0x01f3,((low_sec << 24) >> 24)) //b0-7
    out_port8(0x01f4,(high_sec << 8) >> 8) //b32-39
    out_port8(0x01f4,(((low_sec >> 8) << 24) >> 24)) //b8-15
    out_port8(0x01f5,(high_sec >> 8) //b40-47
    out_port8(0x01f5,(((low_sec >> 16) << 24) >> 24)) //b16-23
    out_port8(0x01f6,0b01000000) //MasterDsk
    out_port8(0x01f7,0x24) //Read
    while()
    {

    }
    
}