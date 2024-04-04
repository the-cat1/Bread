/**
 * Bread
 * window/window.c
 *
 * 对窗口的操作。
 */

#include "window.h"

#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "bread.h"
#include "util/list.h"

static BList *bwindows;
static BList *bwindow_classes;

// 在 window/windowproc.c 中定义
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void BInitWindow() {
    bwindows = BListCreate(sizeof(BWindow));
    bwindow_classes = BListCreate(sizeof(BWindowClass));
}

void BQuitWindow() {
    BListFree(bwindows);
    BListFree(bwindow_classes);
}

BWindowClassID BRegisterWindowClass(HINSTANCE instance, char *classname,
                                    UINT style, HBRUSH background, HICON icon,
                                    HCURSOR cursor) {
    WNDCLASS wc;
    BWindowClass bwc;

    if (instance == NULL || classname == NULL)
        return -1;

    ZeroMemory(&wc, sizeof wc);
    wc.hInstance = instance;
    wc.lpszClassName = classname;
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.style = (style == -1 ? CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW : style);
    wc.hbrBackground = (background ? background : NULL);
    wc.hIcon = (icon ? icon : BGetBreadIcon());
    wc.hCursor = (cursor ? cursor : LoadCursor(NULL, IDC_ARROW));

    if (!RegisterClass(&wc))
        return -1;

    bwc.classname = malloc(strlen(classname) + 1);
    bwc.wcb_keydown = NULL;
    strcpy(bwc.classname, classname);
    BListAppend(bwindow_classes, &bwc);

    return bwindow_classes->len - 1;
}

BWindowID BCreateWindow(BWindowClassID wcid, char *title, int style,
                        HINSTANCE instance, int x, int y, int width, int height,
                        HWND parent, HMENU menu) {
    HWND hWnd;
    BWindow window;
    char *classname = BGetWindowClassByID(wcid)->classname;

    if (wcid < 0 || instance == NULL)
        return -1;

    hWnd = CreateWindow(classname, title == NULL ? "Bread Window" : title,
                        style == -1 ? WS_OVERLAPPEDWINDOW | WS_VISIBLE : style,
                        x == -1 ? CW_USEDEFAULT : x,
                        y == -1 ? CW_USEDEFAULT : y, width == -1 ? 360 : width,
                        height == -1 ? 240 : height, parent, menu, instance, 0);

    if (hWnd = NULL)
        return -1;

    window.hWnd = hWnd;
    window.wcid = wcid;
    BListAppend(bwindows, &window);

    return bwindows->len - 1;
}

void BShowWindow(BWindowID wid, int cmdShow) {
    BWindow *window = BListGet(bwindows, wid);
    ShowWindow(window->hWnd, cmdShow);
    UpdateWindow(window->hWnd);
}

int BMessageLoop(BWindowID wid, BWCBUpdate wcb_update) {
    MSG msg;
    BWindow *window = BGetWindowByID(wid);
    if (!window)
        return -1;

    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            if (wcb_update)
                wcb_update(wid);
        }
    }

    return msg.wParam;
}

void BWindowDrawScreenBuffer(BWindowID wid, BScreenBuffer *sbuffer) {
    HDC hDC, hDCMemory;
    HBITMAP hbitmap;
    BITMAP bitmap;
    int bits_size;
    char *bits;
    int x, y;

    BWindow *window = BGetWindowByID(wid);
    if (!window)
        return;

    hDC = GetDC(window->hWnd);
    hDCMemory = CreateCompatibleDC(hDC);
    hbitmap = CreateCompatibleBitmap(hDC, sbuffer->width, sbuffer->height);
    SelectObject(hDCMemory, hbitmap);

    GetObject(hbitmap, sizeof(bitmap), &bitmap);
    bits_size = bitmap.bmWidthBytes * bitmap.bmHeight;
    bits = malloc(bits_size);
    for (y = 0; y < sbuffer->height; y++) {
        for (x = 0; x < sbuffer->width; x++) {
            int bits_start = y * bitmap.bmWidthBytes + x * 4;
            int sbuffer_index = y * sbuffer->width + x;
            bits[bits_start + 0] = BGET_R(sbuffer->buffer[sbuffer_index]);
            bits[bits_start + 1] = BGET_G(sbuffer->buffer[sbuffer_index]);
            bits[bits_start + 2] = BGET_B(sbuffer->buffer[sbuffer_index]);
        }
    }
    SetBitmapBits(hbitmap, bits_size, bits);
    free(bits);

    BitBlt(hDC, 0, 0, sbuffer->width, sbuffer->height, hDCMemory, 0, 0,
           SRCCOPY);

    DeleteObject(hbitmap);
    DeleteDC(hDCMemory);
    DeleteDC(hDC);
}

void BScreenBufferCreate(BScreenBuffer *sbuffer, int width, int height) {
    sbuffer->buffer = malloc(width * height * sizeof(BColor));
    sbuffer->width = width;
    sbuffer->height = height;
}

BWindowID BGetWindowIDByHwnd(HWND hWnd) {
    int i;
    BWindow *window;

    for (i = 0; i < bwindows->len; i++) {
        window = BListGet(bwindows, i);
        if (window->hWnd = hWnd)
            return i;
    }

    return -1;
}

BWindow *BGetWindowByHwnd(HWND hWnd) {
    int wid = BGetWindowIDByHwnd(hWnd);

    if (wid < 0)
        return NULL;
    return BListGet(bwindows, wid);
}

BWindow *BGetWindowByID(BWindowID wid) { return BListGet(bwindows, wid); }

BWindowClass *BGetWindowClassByID(BWindowClassID wcid) {
    return BListGet(bwindow_classes, wcid);
}
