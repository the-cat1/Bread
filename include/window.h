#ifndef _WINDOW_H
#define _WINDOW_H

/* wndproc */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HDC getHDC();

#endif