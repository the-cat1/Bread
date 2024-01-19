/**
 * Bread
 *
 * window/wndproc.c
 * 窗口的回调函数。
 */

#include <stdio.h>

#include "bread.h"
#include "util.h"
#include "window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    BWindow *window = BGetWindow(hwnd);

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }

    return 0;
}
