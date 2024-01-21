#include <stdlib.h>
#include <string.h>

#include "bread.h"

BList *BList_create(size_t esize)
{
    BList *list;

    list = malloc(sizeof(BList));
    list->esize = esize;
    list->len = 0;
    list->datas = malloc(LIST_MIN_LENGTH * esize);

    return list;
}

void BList_append(BList *list, void *element)
{
    list->len++;
    list->datas = realloc(list->datas, list->len * list->esize);
    memcpy(list->datas + (list->len - 1) * list->esize, element, list->esize);
}

void BList_remove_last(BList *list)
{
    if (list->len <= 0)
        return;

    list->len--;
    if (list->len >= LIST_MIN_LENGTH)
        list->datas = realloc(list->datas, list->len * list->esize);
}

void *BList_get(BList *list, unsigned int index)
{
    if (index < list->len)
        return list->datas + list->esize * index;
    else
        return NULL;
}

void *list_get_last(BList *list)
{
    if (list->len > 0)
    {
        return BList_get(list, list->len - 1);
    }
    else
    {
        return NULL;
    }
}

void BList_free(BList *list)
{
    free(list->datas);
    free(list);
}
