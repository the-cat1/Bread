/**
 * Bread
 *
 * window/wndproc.c
 * 窗口的回调函数。
 */

#include <stdio.h>

#include "bread.h"
#include "window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    BWindowID wid;
    BWindowClass *window;

    wid = BGetWindowIDByHwnd(hwnd);
    if (wid < 0)
        goto defwinproc;
    window = BGetWindowClassByID(BGetWindowByID(wid)->wcid);
    if (!window)
        goto defwinproc;

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (window->wcb_keydown)
            window->wcb_keydown(wid);
        else
            goto defwinproc;

    default:
        goto defwinproc;
        break;
    }

    return 0;

defwinproc:
    return DefWindowProc(hwnd, message, wParam, lParam);
}
