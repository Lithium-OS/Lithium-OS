#include "../../inc/type.h"
struct fat32_file_packet
{
    uint32_t cluster;
    uint32_t sector;
    uint16_t sec_length;
    uint32_t byte_length;
};
