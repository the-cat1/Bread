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

void draw_point_i(BScreenBuffer *sbuffer, BVector2i p, BColor color);
void draw_point_f(BScreenBuffer *sbuffer, BVector2f p, BColor color);

void BRendSceneCreate(BRendScene *rscene) {
    rscene->objects = BListCreate(sizeof(BRendObject));
}

void BRendSceneAddObject(BRendScene *rscene, BRendObject *robject) {
    BListAppend(rscene->objects, robject);
}

void BRendSceneFree(BRendScene *rscene) { free(rscene->objects); }

BVector2f BCameraPositionToScreenPosition(BVector2f cpos, int swidth,
                                          int sheight) {
    // 用右移一位代替除以二
    return (BVector2f){(cpos.x + (swidth >> 1)), (-cpos.y + (sheight >> 1))};
}

#define CAMERA_POS_TO_SCREEN_POS(p)                                            \
    (BCameraPositionToScreenPosition((p), sbuffer->width, sbuffer->height))
void BRendRendScene(BScreenBuffer *sbuffer, BRendScene *rscene) {
    int i;
    BRendObject *robject;

    for (i = 0; i < rscene->objects->len; i++) {
        robject = BListGet(rscene->objects, i);

        switch (robject->type) {
        case BPOINT: {
            BVector2f p = CAMERA_POS_TO_SCREEN_POS(robject->data.point.p);
            draw_point_f(sbuffer, p, robject->data.point.color);
            break;
        }

        case BLINE: {
            BVector2f p1_f = CAMERA_POS_TO_SCREEN_POS(robject->data.line.p1);
            BVector2f p2_f = CAMERA_POS_TO_SCREEN_POS(robject->data.line.p2);
            draw_line(sbuffer, p1_f, p2_f, robject->data.line.color);
            break;
        }

        case BTRIANGLE: {
            BVector2f p1 = CAMERA_POS_TO_SCREEN_POS(robject->data.triangle.p1);
            BVector2f p2 = CAMERA_POS_TO_SCREEN_POS(robject->data.triangle.p2);
            BVector2f p3 = CAMERA_POS_TO_SCREEN_POS(robject->data.triangle.p3);

            draw_triangle(sbuffer, p1, p2, p3, robject->data.triangle.color);
        }

        default:
            break;
        }
    }
}
#undef CAMERA_POS_TO_SCREEN_POS

void draw_point_i(BScreenBuffer *sbuffer, BVector2i p, BColor color) {
    if (p.x < sbuffer->width && p.x >= 0 && p.y < sbuffer->height && p.y > 0)
        sbuffer->buffer[p.x + p.y * sbuffer->width] = color;
}

void draw_point_f(BScreenBuffer *sbuffer, BVector2f p, BColor color) {
    draw_point_i(sbuffer, BVector2fTo2i(p), color);
}

void draw_line(BScreenBuffer *sbuffer, BVector2f p1_f, BVector2f p2_f,
               BColor color) {
    BVector2i p1 = BVector2fTo2i(p1_f);
    BVector2i p2 = BVector2fTo2i(p2_f);

    float temp;
    bool steep; // 是否很斜
    int x, y, dx, dy, error, derror;

    // * 以下代码参考自 https://github.com/ssloy/tinyrenderer
    //   原理参考自 https://www.bilibili.com/video/BV1fe411T7TU/
    //             https://www.bilibili.com/video/BV15Y4y1N71C/
    //             https://www.bilibili.com/video/BV1pN4y1N7zD/
    //             等视频。

    steep = false;
    if (abs(p1.x - p2.x) < abs(p1.y - p2.y)) {
        SWAP(p1.x, p1.y, temp);
        SWAP(p2.x, p2.y, temp);
        steep = true;
    }
    if (p1.x > p2.x) {
        SWAP(p1.x, p2.x, temp);
        SWAP(p1.y, p2.y, temp);
    }

    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    error = 0;
    derror = abs(dy) * 2;
    for (x = p1.x, y = p1.y; x <= p2.x; x++) {
        draw_point_i(sbuffer, steep ? ((BVector2i){y, x}) : ((BVector2i){x, y}),
                     color);

        error += derror;
        if (error > dx) {
            y += (p2.y > p1.y ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void draw_triangle(BScreenBuffer *sbuffer, BVector2f p1, BVector2f p2,
                   BVector2f p3, BColor color) {
    int x, y;

    for (y = 0; y < sbuffer->height; y++) {
        for (x = 0; x < sbuffer->width; x++) {
            int E12 = -(x - p1.x) * (p2.y - p1.y) + (y - p1.y) * (p2.x - p1.x);
            int E23 = -(x - p2.x) * (p3.y - p2.y) + (y - p2.y) * (p3.x - p2.x);
            int E31 = -(x - p3.x) * (p1.y - p3.y) + (y - p3.y) * (p1.x - p3.x);
            if (E12 >= 0 || E23 >= 0 || E31 >= 0)
                continue;

            draw_point_i(sbuffer, (BVector2i){x, y}, color);
        }
    }
}
