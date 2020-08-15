#include "../../inc/type.h"
u32 fat1_location = 0;
u32 fat_length = 0;
u32 root_dir_location = 0;
u32 data_location = 0;
u32* fat_ptr = 0x00000000;
static int fat32_init_func(u32 fat1_loca,u32 fat_len,u32 root_dir_loca,u32 dataf3)
{
    fat1_location = fat1_loca;
    fat_length = fat_len;
    root_dir_location = root_dir_loca;
    data_location = dataf3;

}
u8 sec_temp[512]={1};
u8 utest(u8 tes){
    tes = 15;
    return tes;
}
int main()
{
  utest('A');
}
