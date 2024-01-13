#ifndef _UTIL_H
#define _UTIL_H

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#undef size_t
typedef unsigned long long size_t;
#endif /* _SIZE_T_DEFINED */

/* BList */
// List最小的长度，不能为 0
#define LIST_MIN_LENGTH 1

/* BList */
typedef struct
{
    char *datas;
    unsigned int len;
    size_t esize;
} BList;

/* BList */
BList *BList_create(size_t esize);
void BList_append(BList *list, void *element);
void BList_remove_last(BList *list);
void *BList_get(BList *list, unsigned int index);
void BList_free(BList *list);

#endif
