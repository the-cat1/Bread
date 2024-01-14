#include <windows.h>
#include <stdbool.h>

#include "bread.h"
#include "window.h"
#include "util.h"

BList *windows;

void BInitWindow()
{
    windows = BList_create(sizeof(struct _Window));
}

void BQuitWindow()
{
    BList_free(windows);
}

int BRegisterClass(HINSTANCE instance, char *classname, UINT style, HBRUSH background, HICON icon, HCURSOR cursor)
{
    WNDCLASS wc;

    if (instance == NULL || classname == NULL)
        return false;

    ZeroMemory(&wc, sizeof wc);
    wc.hInstance = instance;
    wc.lpszClassName = classname;
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.style = (style == -1 ? CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW : style);
    wc.hbrBackground = (background ? background : (HBRUSH)GetStockObject(BLACK_BRUSH));
    wc.hIcon = (icon ? icon : getBreadIcon());
    wc.hCursor = (cursor ? cursor : LoadCursor(NULL, IDC_ARROW));

    return RegisterClass(&wc);
}

WindowID BCreateWindow(char *classname, char *title, int style, HINSTANCE instance,
                       int x, int y, int width, int height, HWND parent, HMENU menu)
{
    HWND hwnd;
    Window window;

    if (classname == NULL || instance == NULL)
        return -1;

    hwnd = CreateWindow(
        classname,
        title == NULL ? "Bread Window" : title,
        style == -1 ? WS_OVERLAPPEDWINDOW | WS_VISIBLE : style,
        x == -1 ? CW_USEDEFAULT : x,
        y == -1 ? CW_USEDEFAULT : y,
        width == -1 ? 360 : width,
        height == -1 ? 240 : height,
        parent,
        menu,
        instance,
        0);

    if (hwnd = NULL)
        return -1;

    window.hwnd = hwnd;
    BList_append(windows, &window);

    return windows->len - 1;
}

void BShowWindow(WindowID wid, int cmdShow)
{
    Window *window = BList_get(windows, wid);
    ShowWindow(window->hwnd, cmdShow);
    UpdateWindow(window->hwnd);
}

int BMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

Window *BGetWindow(HWND hwnd)
{
    int i;
    Window *window;

    for (i = 0; i < windows->len; i++)
    {
        window = BList_get(windows, i);
        if (window->hwnd = hwnd)
            return window;
    }

    return NULL;
}
