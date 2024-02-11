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

void draw_point(BScreenBuffer *sbuffer, BVector2i p, BColor color);

#define SWAP_INT(a, b)                                                         \
    (a) ^= (b);                                                                \
    (b) ^= (a);                                                                \
    (a) ^= (b)

void BRendSceneCreate(BRendScene *rscene) {
    rscene->objects = BListCreate(sizeof(BRendObject));
}

void BRendSceneAddObject(BRendScene *rscene, BRendObject *robject) {
    BListAppend(rscene->objects, robject);
}

void BRendSceneFree(BRendScene *rscene) { free(rscene->objects); }

BVector2i BCameraPositionToScreenPosition(BVector2f cpos, int swidth,
                                          int sheight) {
    // 用右移一位代替除以二，加 0.5 是为了四舍五入。
    int x = (int)(cpos.x + (swidth >> 1) + 0.5);
    int y = (int)(-cpos.y + (sheight >> 1) + 0.5);
    return (BVector2i){.x = x, .y = y};
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
            BVector2i p = CAMERA_POS_TO_SCREEN_POS(robject->data.point.p);
            draw_point(sbuffer, p, robject->data.point.color);
            break;
        }

        case BLINE: {
            BVector2i p1 = CAMERA_POS_TO_SCREEN_POS(robject->data.line.p1);
            BVector2i p2 = CAMERA_POS_TO_SCREEN_POS(robject->data.line.p2);
            bool steep; // 是否很斜
            int x, y, dx, dy, error, derror;

            // * 以下代码参考自 https://github.com/ssloy/tinyrenderer
            //   原理参考自 https://www.bilibili.com/video/BV1fe411T7TU/
            //             https://www.bilibili.com/video/BV15Y4y1N71C/
            //             https://www.bilibili.com/video/BV1pN4y1N7zD/
            //             等视频。

            steep = false;
            if (abs(p1.x - p2.x) < abs(p1.y - p2.y)) {
                SWAP_INT(p1.x, p1.y);
                SWAP_INT(p2.x, p2.y);
                steep = true;
            }
            if (p1.x > p2.x) {
                SWAP_INT(p1.x, p2.x);
                SWAP_INT(p1.y, p2.y);
            }

            dx = p2.x - p1.x;
            dy = p2.y - p1.y;
            error = 0;
            derror = abs(dy) * 2;
            for (x = p1.x, y = p1.y; x <= p2.x; x++) {
                draw_point(sbuffer,
                           steep ? ((BVector2i){y, x}) : ((BVector2i){x, y}),
                           robject->data.line.color);

                error += derror;
                if (error > dx) {
                    y += (p2.y > p1.y ? 1 : -1);
                    error -= dx * 2;
                }
            }
            break;
        }

        default:
            break;
        }
    }
}
#undef CAMERA_POS_TO_SCREEN_POS

void draw_point(BScreenBuffer *sbuffer, BVector2i p, BColor color) {
    if (p.x < sbuffer->width && p.x >= 0 && p.y < sbuffer->height && p.y > 0)
        sbuffer->buffer[p.x + p.y * sbuffer->width] = color;
}
