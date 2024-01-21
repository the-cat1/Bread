/**
 * bread.h
 * 包括了所有公用函数。
 */

#include <windows.h>

#ifndef _BREAD_H
#define _BREAD_H

/* util */
/* BList */
// List最小的长度，不能为 0
#define LIST_MIN_LENGTH 1

typedef struct
{
    char *datas;
    unsigned int len;
    size_t esize;
} BList;

BList *BList_create(size_t esize);
void BList_append(BList *list, void *element);
void BList_remove_last(BList *list);
void *BList_get(BList *list, unsigned int index);
void BList_free(BList *list);

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

void BInitWindow();
void BQuitWindow();

int BRegisterClass(HINSTANCE instance, char *classname, UINT style, HBRUSH background, HICON icon, HCURSOR cursor);
int BCreateWindow(char *classname, char *title, int style, HINSTANCE instance,
                  int x, int y, int width, int height, HWND parent, HMENU menu);
void BShowWindow(BWindowID wid, int cmdShow);
int BMessageLoop();
BWindow *BGetWindow(HWND hwnd);

#endif
