/**
 * Bread
 * include/math/vector.h
 *
 * 有关向量的定义。
 */

#ifndef _BREAD_MATH_VECTOR2_H
#define _BREAD_MATH_VECTOR2_H

/* BVector2f */
typedef struct {
    float x, y;
} BVector2f;

/* BVector2i */
typedef struct {
    int x, y;
} BVector2i;

#define BVector2fTo2i(vf) ((BVector2i){(int)((vf).x + 0.5), (int)((vf).y + 0.5)})

#endif /* _BREAD_MATH_VECTOR2_H */
