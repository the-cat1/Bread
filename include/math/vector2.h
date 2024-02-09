/**
 * Bread
 * include/math/vector2.h
 *
 * 有关二维向量的定义。
 */

#ifndef _BREAD_MATH_VECTOR2_H
#define _BREAD_MATH_VECTOR2_H

/* BVector2f */
// clang-format off
typedef struct {
    union {
        struct { float x, y; };
        struct { float u, v; };
    };
} BVector2f;
// clang-format on

/* BVector2i */
typedef struct {
    int x, y;
} BVector2i;

#endif /* _BREAD_MATH_VECTOR2_H */
