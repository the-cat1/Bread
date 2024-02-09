/**
 * Bread
 * window/wndproc.c
 *
 * 窗口的回调函数。
 */

#include <stdio.h>

#include "bread.h"
#include "util/list.h"
#include "window.h"

#define DEFWINPROC() DefWindowProc(hWnd, msg, wParam, lParam)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    BWindowID wid;
    BWindow *window;
    BWindowClass *windowclass;

    wid = BGetWindowIDByHwnd(hWnd);
    if (wid < 0)
        return DEFWINPROC();
    window = BGetWindowByID(wid);
    windowclass = BGetWindowClassByID(window->wcid);
    if (!windowclass)
        return DEFWINPROC();

    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return DEFWINPROC();

    case WM_KEYDOWN:
        if (windowclass->wcb_keydown)
            windowclass->wcb_keydown(wid);
        return DEFWINPROC();

    case WM_ERASEBKGND:
        return DEFWINPROC();

    case WM_PAINT:
        return DEFWINPROC();

    default:
        return DEFWINPROC();
    }
}
