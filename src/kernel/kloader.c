#include "../lib/type.h"
extern uint32_t fat32_get_rootfile(uint8_t name[8],uint32_t* file_ptr);

void load(){
    char name[8]={'k','e','r','n','e','l',' ',' '};
    fat32_get_rootfile(name,(uint32_t*)0x100000);
}

