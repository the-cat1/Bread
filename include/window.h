/**
 * Bread
 * include/window.h
 * 
 * 有关窗口的操作。
 */

#include <windows.h>

#ifndef _BREAD_WINDOW_H
#define _BREAD_WINDOW_H

typedef int BWindowID;
typedef int BWindowClassID;

// Window Callback
typedef void (*BWCBKeydown)(BWindowID);
typedef void (*BWCBUpdate)(BWindowID);

typedef struct
{
    HWND hWnd;
    BWindowClassID wcid;
    HDC hDC;
} BWindow;

typedef struct
{
    char *classname;
    BWCBKeydown wcb_keydown;
} BWindowClass;

void BInitWindow();
void BQuitWindow();

BWindowClassID BRegisterWindowClass(HINSTANCE instance, char *classname,
                                    UINT style, HBRUSH background, HICON icon,
                                    HCURSOR cursor);
BWindowID BCreateWindow(BWindowClassID wcid, char *title, int style,
                        HINSTANCE instance, int x, int y, int width,
                        int height, HWND parent, HMENU menu);
void BShowWindow(BWindowID wid, int cmdShow);
int BMessageLoop(BWindowID wid, BWCBUpdate wcb_update);
BWindowID BGetWindowIDByHwnd(HWND hWnd);
BWindow *BGetWindowByHwnd(HWND hWnd);
BWindow *BGetWindowByID(BWindowID wid);
BWindowClass *BGetWindowClassByID(BWindowClassID wcid);

#endif /* _BREAD_WINDOW_H */
