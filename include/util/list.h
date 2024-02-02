/**
 * Bread
 * include/util/list.h
 * 
 * BList 的定义。
 */

#include <corecrt.h>

#ifndef _BREAD_UTIL_LIST_H
#define _BREAD_UTIL_LIST_H

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
void *BListGet(BList *list, unsigned int index);
void BListFree(BList *list);

#endif /* _BREAD_UTIL_LIST_H */
