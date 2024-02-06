/**
 * Bread
 * include/bread.h
 * 
 * Bread 引擎的基本函数。
 */

#include <windows.h>

#ifndef _BREAD_H
#define _BREAD_H

// BColor
typedef int BColor;
#define BRGB(r, g, b) ((r) << 0 | (g) << 8 | (b) << 16)
#define BGET_R(color) (char)(((color) & 0xFF0000) >> 16)
#define BGET_G(color) (char)(((color) & 0x00FF00) >> 8)
#define BGET_B(color) (char)(((color) & 0x0000FF) >> 0)

void BInit();
void BQuit();
HICON BGetBreadIcon();

#endif /* _BREAD_H */
