
#include "ascii.h"

uint32_t video_bas_addr = 0x00;
uint32_t video_lim_x = 0x00;
uint32_t video_lim_y = 0x00;

uint32_t vdp_write_pixel(uint8_t r,uint8_t g,uint8_t b,uint32_t x,uint32_t y)                                   //点个像素到物理地址
{
    uint32_t* ptr = video_bas_addr + ((x * 32)+(y * 32 * video_lim_x));

    uint32_t pixel = 0x00;

    pixel = r;
    pixel = pixel << 24;
    pixel = g;
    pixel = pixel << 16;
    pixel = b;
    pixel = pixel << 8;

    *ptr = pixel;
    return 0;
}
uint32_t vdp_write_hline(uint8_t r,uint8_t g,uint8_t b,uint32_t start_x,uint32_t end_x,uint32_t y)              //画个横线到物理地址
{
    uint32_t tmpx = start_x;
    for (uint32_t i = 0; i < ((end_x - start_x)+ 1); i++)
    {
        vdp_write_pixel(r,g,b,tmpx,y);
        tmpx++;
    }
    return 0;
}
uint32_t vdp_write_vline(uint8_t r,uint8_t g,uint8_t b,uint32_t start_y,uint32_t end_y,uint32_t x)              //画个竖线到物理地址
{
    uint32_t tmpy = start_y;
    for (uint32_t i = 0; i < ((end_y - start_y)+ 1);i++)
    {
        vdp_write_pixel(r,g,b,tmpy,x);
        tmpy++;
    }
    return 0;
}
uint32_t vdp_write_rect(uint8_t r,uint8_t g,uint8_t b,uint32_t org_x,uint32_t org_y,uint32_t h,uint32_t w)      //画一个矩形到物理地址
{
    uint32_t tmpy = org_y;
    for (uint32_t i = 0; i < h;i++)
    {
        vdp_write_hline(r,g,b,tmpy,tmpy + w,org_x);
        tmpy++;
    }
    return 0;
}
uint32_t vdp_write_ascii(uint32_t x,uint32_t y,uint8_t num)                                                     //写ASCII到字符地址
{
    uint32_t ob_x = x * 8;
    uint32_t ob_y = y * 16;
    uint8_t* tmp = asciifont[num];
    for (uint32_t i = 0; i < 16; i++)
    {
        ob_x = x * 8;
        for (uint32_t i = 0; i < 8; i++)
        {
            if(((*tmp << (8 - i)) >> 7))
            {
                vdp_write_pixel(0xff,0xff,0xff,ob_x,ob_y);
            }
            ob_x++;
        }

    tmp++;
    ob_y++;
    }
    return 0;
    
}
uint32_t vdp_write_string(uint8_t* ptr,uint16_t len,uint32_t x,uint32_t y)                                      //写字符串到字符地址
{
    uint32_t tmpx = x;
    for (uint32_t i = 0; i < len; i++)
    {
        vdp_write_ascii(tmpx,y,*ptr);
        tmpx++;
        ptr++;
    }
    
}
/*             Disable AlanCui 2020/8/15
uint32_t vdp_write_unicode(uint32_t x,uint32_t y,uint8_t num)
{
    uint32_t ob_x = x * 16;
    uint32_t ob_y = y * 16;
    uint16_t* tmp = unifont[num];
    for (uint32_t i = 0; i < 16; i++)
    {
        ob_x = x * 8;
        for (uint32_t i = 0; i < 16; i++)
        {
            if(((*tmp << (16 - i)) >> 15))
            {
                vdp_write_pixel(0xff,0xff,0xff,ob_x,ob_y);
            }
            ob_x++;
        }

    tmp++;
    ob_y++;
    }
    return 0;
    
}
*/