/**
 * Bread
 * graphics/render.c
 *
 * 渲染程序。
 */

#include "graphics/render.h"

#include "util/list.h"
#include "window.h"

void draw_point(BScreenBuffer *sbuffer, BVector2i p, BColor color);

void BRendSceneCreate(BRendScene *rscene) {
    rscene->objects = BListCreate(sizeof(BRendObject));
}

void BRendSceneAddObject(BRendScene *rscene, BRendObject *robject) {
    BListAppend(rscene->objects, robject);
}

void BRendSceneFree(BRendScene *rscene) { free(rscene->objects); }

void BRendRendScene(BScreenBuffer *sbuffer, BRendScene *rscene) {
    int i;
    BRendObject *robject;

    for (i = 0; i < rscene->objects->len; i++) {
        robject = BListGet(rscene->objects, i);

        switch (robject->type) {
        case BPOINT:
            draw_point(sbuffer,
                       BCameraPositionToScreenPosition(robject->data.point.p,
                                                       sbuffer->width,
                                                       sbuffer->height),
                       robject->data.point.color);
            break;

        default:
            break;
        }
    }
}

void draw_point(BScreenBuffer *sbuffer, BVector2i p, BColor color) {
    sbuffer->buffer[p.x + p.y * sbuffer->width] = color;
}

BVector2i BCameraPositionToScreenPosition(BVector2f cpos, int swidth,
                                          int sheight) {
    // 用右移一位代替除以二，加 0.5 是为了四舍五入。
    int x = (int)(cpos.x + (swidth >> 1) + 0.5);
    int y = (int)(cpos.y + (sheight >> 1) + 0.5);
    return (BVector2i){.x = x, .y = y};
}
