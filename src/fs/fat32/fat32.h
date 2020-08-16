#include "../../inc/type.h"
typedef struct
{
    uint32_t cluster;
    uint32_t sector;
    uint16_t sec_length;
    uint32_t byte_length;
}fat32_file_packet;
