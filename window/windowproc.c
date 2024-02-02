/**
 * Bread
 * window/wndproc.c
 * 
 * 窗口的回调函数。
 */

#include <stdio.h>

#include "bread.h"
#include "window.h"
#include "util/list.h"

#define DEFWINPROC() DefWindowProc(hWnd, msg, wParam, lParam)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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

    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (windowclass->wcb_keydown)
            windowclass->wcb_keydown(wid);
        else
            return DEFWINPROC();
        break;

    case WM_ERASEBKGND:
        break;

    /**
     * 这里的方法是我自己想的，不知道对不对，有没有BUG，但是能用。
     * 如果你有更好的方法，请提出来！
     */
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC_;
        window->hDC = BeginPaint(hWnd, &ps);
        break;
    }

    default:
        return DEFWINPROC();
        break;
    }

    return 0;
}
