#include <stdlib.h>
#include <memory.h>

#include "bread.h"

BList *BListCreate(size_t esize)
{
    BList *list;

    list = malloc(sizeof(BList));
    list->esize = esize;
    list->len = 0;
    list->datas = malloc(BLIST_MIN_LENGTH * esize);

    return list;
}

void BListAppend(BList *list, void *element)
{
    list->len++;
    list->datas = realloc(list->datas, list->len * list->esize);
    memcpy(list->datas + (list->len - 1) * list->esize, element, list->esize);
}

void *BListGet(BList *list, unsigned int index)
{
    if (index < list->len)
        return list->datas + list->esize * index;
    else
        return NULL;
}

void BListFree(BList *list)
{
    free(list->datas);
    free(list);
}
