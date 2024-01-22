/**
 * bread.h
 * 包括了所有公用函数。
 */

#include <windows.h>

#ifndef _BREAD_H
#define _BREAD_H

/* util */
/* BList */
// BList最小的长度，不能为 0
#define BLIST_MIN_LENGTH 1

typedef struct
{
    char *datas;
    unsigned int len;
    size_t esize;
} BList;

BList *BListCreate(size_t esize);
void BListAppend(BList *list, void *element);
void BListRemoveLast(BList *list);
void *BListGet(BList *list, unsigned int index);
void BListFree(BList *list);

/* bread.c */
void BInit();
void BQuit();
HICON BGetBreadIcon();

/* window.c */
typedef int BWindowID;
typedef struct
{
    HWND hwnd;
} BWindow;
typedef int BWindowClassID;
typedef struct
{
    char *classname;
} BWindowClass;

void BInitWindow();
void BQuitWindow();

BWindowClassID BRegisterWindowClass(HINSTANCE instance, char *classname, UINT style, HBRUSH background, HICON icon, HCURSOR cursor);
BWindowID BCreateWindow(BWindowClassID wcid, char *title, int style, HINSTANCE instance,
                        int x, int y, int width, int height, HWND parent, HMENU menu);
void BShowWindow(BWindowID wid, int cmdShow);
int BMessageLoop();
BWindow *BGetWindow(HWND hwnd);
BWindowClass *BGetWindowClass(BWindowClassID wcid);

#endif
