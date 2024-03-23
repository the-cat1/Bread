/**
 * Bread
 * include/graphics/render.h
 *
 * 场景的渲染
 */

#ifndef _BREAD_GRAPHICS_RENDER_H
#define _BREAD_GRAPHICS_RENDER_H

#include "math/vector.h"
#include "util/list.h"
#include "window.h"

typedef struct {
    BList *objects;
} BRendScene;

enum BRendObjectType { BPOINT, BLINE, BTRIANGLE };

typedef struct {
    enum BRendObjectType type;
    union {
        // BPOINT
        struct {
            BVector2f p;
            BColor color;
        } point;

        // BLINE
        struct {
            BVector2f p1, p2;
            BColor color;
        } line;

        // BTRIANGLE
        struct {
            BVector2f p1, p2, p3;
            BColor color;
        } triangle;
    } data;
} BRendObject;

BVector2f BCameraPositionToScreenPosition(BVector2f cpos, int swidth,
                                          int sheight);

void BRendSceneCreate(BRendScene *rscene);
void BRendSceneAddObject(BRendScene *rscene, BRendObject *robject);
void BRendSceneFree(BRendScene *rscene);

void BRendRendScene(BScreenBuffer *sbuffer, BRendScene *rscene);

#endif /* _BREAD_GRAPHICS_RENDER_H */
