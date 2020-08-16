
#define _UNIFONT_ONLY_ASCII
#include "unifont.h"

uint32_t video_bas_addr = 0x00;
uint32_t video_lim_x = 0x00;
uint32_t video_lim_y = 0x00;

// 颜色结构，布局为 RGBA
typedef struct
{
    // 红色值
    uint8_t r;
    // 绿色值
    uint8_t g;
    // 蓝色值
    uint8_t b;
    // alpha 值（不透明度）
    uint8_t a;
} color_t;

// 常用的控制台颜色值
color_t shell_colors[16] =
{
    // 黑色
    {0, 0, 0, 0},
    // 暗红色
    {128, 0, 0, 0},
    // 暗绿色
    {0, 128, 0, 0},
    // 暗黄色
    {128, 128, 0, 0},
    // 暗蓝色
    {0, 0, 128, 0},
    // 紫色
    {128, 0, 128, 0},
    // 暗青色
    {0, 128, 128, 0},
    // 淡灰色
    {192, 192, 192, 0},
    // 灰色
    {128, 128, 128, 0},
    // 红色
    {255, 0, 0, 0},
    // 绿色
    {0, 255, 0, 0},
    // 黄色
    {255, 255, 0, 0},
    // 蓝色
    {0, 0, 255, 0},
    // 粉红色
    {255, 0, 255, 0},
    // 青色
    {0, 255, 255, 0},
    // 白色
    {255, 255, 255, 0}
};

// 绘制一个像素到物理地址
uint32_t
vdp_draw_pixel(
    uint32_t x,
    uint32_t y,
    color_t *color
    )
{
    uint32_t *ptr = video_bas_addr + ((x * 32) + (y * 32 * video_lim_x));

    uint32_t pixel = 0x00;
    if (color)
        pixel = (color->r << 24) | (color->g << 16) | (color->b << 8);
    else
        pixel = (shell_colors[15].r << 24) |
                (shell_colors[15].g << 16) |
                (shell_colors[15].b << 8);

    *ptr = pixel;
    return 0;
}

// 绘制横线到物理地址
uint32_t vdp_draw_hline(
    uint32_t start_x,
    uint32_t end_x,
    uint32_t y,
    color_t *color
    )
{
    uint32_t tmpx = start_x;
    for (uint32_t i = 0; i < ((end_x - start_x) + 1); i++)
    {
        vdp_draw_pixel(tmpx, y, color);
        tmpx++;
    }
    return 0;
}

// 绘制竖线到物理地址
uint32_t vdp_draw_vline(
    uint32_t start_y,
    uint32_t end_y,
    uint32_t x,
    color_t *color
    )
{
    uint32_t tmpy = start_y;
    for (uint32_t i = 0; i < ((end_y - start_y) + 1); i++)
    {
        vdp_draw_pixel(tmpy, x, color);
        tmpy++;
    }
    return 0;
}

uint32_t abs(uint32_t a)
{
    return a < 0 ? -a : a;
}

uint32_t vdp_draw_line(
    uint32_t x0,
    uint32_t y0,
    uint32_t x1,
    uint32_t y1,
    color_t *color
    )
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (vdp_draw_pixel(x0, y0, color), x0 != x1 || y0 != y1) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
    return 0;
}

// 绘制一个矩形到物理地址
uint32_t vdp_draw_rect(
    uint32_t org_x,
    uint32_t org_y,
    uint32_t h,
    uint32_t w,
    color_t *color
    )
{
    uint32_t tmpy = org_y;
    for (uint32_t i = 0; i < h; i++)
    {
        vdp_draw_hline(tmpy, tmpy + w, org_x, color);
        tmpy++;
    }
    return 0;
}

// 绘制 Unicode 到字符地址，返回字符宽度
uint8_t vdp_draw_unicode(
    uint32_t x,
    uint32_t y,
    uint16_t unicode,
    color_t *color
    )
{
    // 获取这个字符字体的宽度，1 半角，2 全角，0 不存在字体
    uint8_t width = unifont_width[unicode];
    if (width)
    {
        uint32_t ob_x = x * 8;
        uint32_t ob_y = y * 16;
        uint8_t *tmp = unifont[unicode];
        for (uint32_t i = 0; i < 16; i++)
        {
            ob_x = x * 8 * width;
            for (uint32_t j = 0; j < 8 * width; j++)
            {
                if (((*tmp << (8 * width - j)) >> 7))
                {
                    vdp_draw_pixel(ob_x, ob_y, color);
                }
                ob_x++;
            }

            tmp++;
            ob_y++;
        }
    }
    else
    {
        // 如果找不到字就绘制 null 字
        return vdp_draw_unicode(x, y, 0, color);
    }
    return width;
}

// 写字符串到字符地址（不会自动换行）
uint32_t vdp_draw_string(
    uint8_t *string,
    uint16_t len,
    uint32_t x,
    uint32_t y,
    color_t *color
    )
{
    // 字体大小有两个：8 * 16, 16 * 16
    uint32_t tmpx = x;
    for (uint32_t i = 0; i < len; i++)
    {
        tmpx += vdp_draw_unicode(tmpx, y, *string, color) * 8;
        string++;
    }
}
