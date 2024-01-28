/**
 * Bread
 *
 * window/wndproc.c
 * 窗口的回调函数。
 */

#include <stdio.h>

#include "bread.h"
#include "window.h"

HDC hDC = 0;
HDC getHDC() { return hDC; };

#define DEFWINPROC() DefWindowProc(hWnd, message, wParam, lParam)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    BWindowID wid;
    BWindowClass *window;

    wid = BGetWindowIDByHwnd(hWnd);
    if (wid < 0)
        return DEFWINPROC();
    window = BGetWindowClassByID(BGetWindowByID(wid)->wcid);
    if (!window)
        return DEFWINPROC();

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (window->wcb_keydown)
            window->wcb_keydown(wid);
        else
            return DEFWINPROC();
        break;

    case WM_ERASEBKGND:
        break;

    /* 
     * 这里的方法是我自己想的，不知道对不对，有没有BUG，但是能用。
     * 如果你有更好的方法，请提出来！
     */
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC_;
        hDC_ = BeginPaint(hWnd, &ps);
        hDC = hDC_;
        break;
    }

    default:
        return DEFWINPROC();
        break;
    }

    return 0;
}
