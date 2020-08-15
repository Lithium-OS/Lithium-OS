#include "fat32.h"
uint32_t fat1_location = 0;
uint32_t fat_length = 0;
uint32_t root_dir_location = 0;
uint32_t root_dir_len = 0;
uint32_t data_location = 0;
extern uint32_t read_disk_sector(uint16_t high_sec,uint32_t low_sec,uint16_t sec_num,uint32_t* target_ptr);
uint32_t fat32_init_func(uint32_t fat1_loca,uint32_t fat_len,uint32_t root_dir_loca,uint32_t dataf3)
{
    fat1_location = fat1_loca;
    fat_length = fat_len;
    root_dir_location = root_dir_loca;
    data_location = dataf3;
    return 0;
}
struct fat32_file_packet fat32_rootfind_file(uint8_t f_name[8])


{
    struct fat32_file_packet opt;
    uint8_t sec_temp[512] = {1};
    uint16_t i = 0;
    while(i < (root_dir_len + 1))
    {
        read_disk_sector(0x00,root_dir_location,i,(uint32_t*)sec_temp); //加载跟目录项

    uint16_t item_ptr = 0;
    while (item_ptr < 17)
    {   
        uint16_t ptr = 0;
        while(ptr < 9)
        {
            if (!(f_name[ptr] = sec_temp[(item_ptr * 32)+ ptr]))    //对比文件名
            {
                goto finp;
            }
            ptr++;
        }

            uint32_t clu_ptr = 0;
            
            clu_ptr = sec_temp[(item_ptr * 32)+ 20];        //获取簇位置
            clu_ptr = (clu_ptr << 24);
            clu_ptr = sec_temp[(item_ptr * 32)+ 21];
            clu_ptr = (clu_ptr << 16);
            clu_ptr = sec_temp[(item_ptr * 32)+ 26];
            clu_ptr = (clu_ptr << 8);
            clu_ptr = sec_temp[(item_ptr * 32)+ 27];

            opt.cluster = clu_ptr;
            opt.sector = ((clu_ptr - 3 )*8 + data_location);

            uint32_t clu_size = 0;

            clu_ptr = sec_temp[(item_ptr * 32)+ 28];        //获取文件大小
            clu_ptr = (clu_ptr << 24);
            clu_ptr = sec_temp[(item_ptr * 32)+ 29];
            clu_ptr = (clu_ptr << 16);
            clu_ptr = sec_temp[(item_ptr * 32)+ 30];
            clu_ptr = (clu_ptr << 8);
            clu_ptr = sec_temp[(item_ptr * 32)+ 31];
            
            opt.byte_length = clu_size;

            uint8_t clu_offs = ((clu_ptr % 16) - 1);
            uint32_t clu_sec = (clu_ptr - (clu_ptr % 16)) / 16;

            read_disk_sector(0x00,(clu_sec + fat1_location),1,(uint32_t*)sec_temp);
            uint32_t clu_item = 0;
            uint32_t clu_count = 0;
            while (!(clu_item = 0x0fffffff))                //计算簇长度
            {
                clu_item = sec_temp[(clu_offs * 4)+ 0];
                clu_item = (clu_item << 24);
                clu_item = sec_temp[(clu_offs * 4)+ 1];
                clu_item = (clu_item << 16);
                clu_item = sec_temp[(clu_offs * 4)+ 2];
                clu_item = (clu_item << 8);
                clu_item = sec_temp[(clu_offs * 4)+ 3];

                clu_offs++;
                clu_count++;
            }

            opt.sec_length = (clu_count * 8);
            return opt;
finp:
    item_ptr++;
    }
    i++;
    }
    opt.sector = 0;
    opt.cluster = 0;
    opt.byte_length = 0;
    opt.sec_length = 0;
    return opt;
}
uint32_t fat32_load_file(struct fat32_file_packet f32fpack,uint32_t* tptr)
{
        return read_disk_sector(0x0000,f32fpack.sector,f32fpack.sec_length,tptr);  
    
}
uint32_t fat32_get_rootfile(uint8_t name[8],uint32_t* file_ptr)
{
        return fat32_load_file(fat32_rootfind_file(name),file_ptr);
}
/*uint32_t fat32_create_rootfile(uint8_t f_name[8],uint8_t f_exname[3])
{
        read_disk_sector(0x0000,fat1_location);
}*/