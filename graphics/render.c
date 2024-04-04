/**
 * Bread
 * graphics/render.c
 *
 * 渲染程序。
 */

#include "graphics/render.h"

#include <math.h>
#include <stdbool.h>

#include "util/list.h"
#include "window.h"

#define SWAP(a, b, t)                                                          \
    (t) = (a);                                                                 \
    (a) = (b);                                                                 \
    (b) = (t)

BVector2f BCameraPositionToScreenPosition(BVector2f cpos, int width,
                                          int height) {
    // 用右移一位代替除以二
    int half_width = width >> 1;
    int half_height = height >> 1;
    return (BVector2f){half_width + cpos.x * half_width,
                       half_height + -cpos.y * half_height};
}

void BDrawPoint(BVector2f p, BScreenBuffer *sbuffer, BPixelShader shader) {
    BPixelShaderContext context;
    context.pixel = BVector2fTo2i(
        BCameraPositionToScreenPosition(p, sbuffer->width, sbuffer->height));
    context.vs_data = NULL;
    shader(context, sbuffer);
}

void BDrawLine(BVector2f p1, BVector2f p2, BScreenBuffer *sbuffer,
               BPixelShader shader) {
    BPixelShaderContext context;
    context.vs_data = NULL;

    BVector2i p1_ = BVector2fTo2i(
        BCameraPositionToScreenPosition(p1, sbuffer->width, sbuffer->height));
    BVector2i p2_ = BVector2fTo2i(
        BCameraPositionToScreenPosition(p2, sbuffer->width, sbuffer->height));

    float temp;
    bool steep; // 是否很斜
    int x, y, dx, dy, error, derror;

    // * 以下代码参考自 https://github.com/ssloy/tinyrenderer

    steep = false;
    if (abs(p1_.x - p2_.x) < abs(p1_.y - p2_.y)) {
        SWAP(p1_.x, p1_.y, temp);
        SWAP(p2_.x, p2_.y, temp);
        steep = true;
    }
    if (p1_.x > p2_.x) {
        SWAP(p1_.x, p2_.x, temp);
        SWAP(p1_.y, p2_.y, temp);
    }

    dx = p2_.x - p1_.x;
    dy = p2_.y - p1_.y;
    error = 0;
    derror = abs(dy) * 2;
    for (x = p1_.x, y = p1_.y; x <= p2_.x; x++) {
        context.pixel = steep ? (BVector2i){y, x} : (BVector2i){x, y};
        shader(context, sbuffer);

        error += derror;
        if (error > dx) {
            y += (p2_.y > p1_.y ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void BDrawTriangle(BVector2f p1, BVector2f p2, BVector2f p3,
                   BScreenBuffer *sbuffer, BPixelShader shader) {
    BPixelShaderContext context;
    context.vs_data = NULL;
    int x, y;

    p1 = BCameraPositionToScreenPosition(p1, sbuffer->width, sbuffer->height);
    p2 = BCameraPositionToScreenPosition(p2, sbuffer->width, sbuffer->height);
    p3 = BCameraPositionToScreenPosition(p3, sbuffer->width, sbuffer->height);

    for (y = 0; y < sbuffer->height; y++) {
        for (x = 0; x < sbuffer->width; x++) {
            int E12 = -(x - p1.x) * (p2.y - p1.y) + (y - p1.y) * (p2.x - p1.x);
            int E23 = -(x - p2.x) * (p3.y - p2.y) + (y - p2.y) * (p3.x - p2.x);
            int E31 = -(x - p3.x) * (p1.y - p3.y) + (y - p3.y) * (p1.x - p3.x);
            if (E12 > 0 || E23 > 0 || E31 > 0)
                continue;

            context.pixel = (BVector2i){x, y};
            shader(context, sbuffer);
        }
    }
}
