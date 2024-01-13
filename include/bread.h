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
HICON getBreadIcon();

/* window */
typedef int WindowID;
typedef void (*WindowDrawEventFunction)(WindowID);
typedef struct _Window
{
    HWND hwnd;
    WindowDrawEventFunction drawEF;
} Window;


void BInitWindow();
void BQuitWindow();

int BRegisterClass(HINSTANCE instance, char *classname, UINT style, HBRUSH background, HICON icon, HCURSOR cursor);
int BCreateWindow(char *classname, char *title, int style, HINSTANCE instance,
                  int x, int y, int width, int height, HWND parent, HMENU menu);
void BShowWindow(WindowID wid, int cmdShow);
int BMessageLoop();
BList *BGetWindows();

#endif
