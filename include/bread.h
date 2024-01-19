/**
 * bread.h
 * 包括了所有公用函数。
 */

#include <windows.h>

#include "util.h"

#ifndef _BREAD_H
#define _BREAD_H

/* bread.c */
void BInit();
void BQuit();
HICON BGetBreadIcon();

/* window */
typedef int WindowID;
typedef struct
{
    HWND hwnd;
} BWindow;

void BInitWindow();
void BQuitWindow();

int BRegisterClass(HINSTANCE instance, char *classname, UINT style, HBRUSH background, HICON icon, HCURSOR cursor);
int BCreateWindow(char *classname, char *title, int style, HINSTANCE instance,
                  int x, int y, int width, int height, HWND parent, HMENU menu);
void BShowWindow(WindowID wid, int cmdShow);
int BMessageLoop();
BWindow *BGetWindow(HWND hwnd);

#endif
