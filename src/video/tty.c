/*Not FIN*//*
#include "../type.h"
extern uint32_t video_bas_addr;
extern uint32_t video_lim_x;
extern uint32_t video_lim_y;
extern uint32_t vdp_write_rect(uint8_t r,uint8_t g,uint8_t b,uint32_t org_x,uint32_t org_y,uint32_t h,uint32_t w);
uint32_t tty_flush(void)
{
    return vdp_write_rect(0x00,0x00,0x00,0,0,video_lim_y,video_lim_x);
}
*/