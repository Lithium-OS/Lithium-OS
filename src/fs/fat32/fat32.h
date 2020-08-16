#include "../../lib/type.h"
typedef struct
{
    uint8_t name[8];
    uint32_t cluster;
    uint32_t sector;
    uint16_t sec_length;
    uint32_t byte_length;
}fat32_file_packet;
typedef struct 
{
    uint8_t name[8];
    uint8_t exname[3];
    uint8_t attr;
    uint8_t rev;
    uint8_t t_create_ms;
    uint16_t t_create_time;
    uint16_t t_create_date;
    uint16_t t_acc_date;
    uint16_t clu_h;
    uint16_t t_write_time;
    uint16_t t_write_date;
    uint16_t clu_l;
    uint32_t size;
}fat32_file_table;

