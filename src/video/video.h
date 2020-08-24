#include "../lib/stdint.h"

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
