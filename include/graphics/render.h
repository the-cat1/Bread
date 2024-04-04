/**
 * Bread
 * include/graphics/render.h
 *
 * 场景的渲染
 */

#ifndef _BREAD_GRAPHICS_RENDER_H
#define _BREAD_GRAPHICS_RENDER_H

#include "bread.h"
#include "math/vector.h"
#include "util/list.h"
#include "window.h"

typedef struct {
    BVector2i pixel;
    void *vs_data;
} BPixelShaderContext;

typedef void (*BPixelShader)(BPixelShaderContext, BScreenBuffer *);

BVector2f BCameraPositionToScreenPosition(BVector2f cpos, int swidth,
                                          int sheight);
void BDrawPoint(BVector2f p, BScreenBuffer *buffer, BPixelShader shader);
void BDrawLine(BVector2f p1, BVector2f p2, BScreenBuffer *sbuffer,
               BPixelShader shader);
void BDrawTriangle(BVector2f p1, BVector2f p2, BVector2f p3,
                   BScreenBuffer *sbuffer, BPixelShader shader);

#endif /* _BREAD_GRAPHICS_RENDER_H */
