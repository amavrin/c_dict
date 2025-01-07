#include "dict.h"

dict *new_dict()
{
    dict *d = malloc(sizeof(dict));
    *d = (dict){.elems = NULL, .size = 0};
    return d;
}

int dict_add(dict *d, char *key, char *value)
{
    if (!d || !key || !value)
    {
        return DICT_BAD_POINTER;
    }
    if (dict_find(d, key))
    {
        if (!dict_del(d, key))
        {
            return DICT_OTHER_ERROR;
        }
    }
    dict_elem *tmp = realloc(d->elems, (d->size + 1) * sizeof(dict_elem));
    if (!tmp)
    {
        return DICT_ALLOC_ERROR;
    }
    d->elems = tmp;
    d->elems[d->size] = (dict_elem){.key = key, .value = value};
    d->size++;
    return DICT_OK;
}

dict_elem *dict_find(dict *d, char *key)
{
    for (int i = 0; i < d->size; i++)
    {
        if (strcmp(d->elems[i].key, key) == 0)
        {
            return &d->elems[i];
        }
    }
    return NULL;
}

bool dict_del(dict *d, char *key)
{
    dict_elem *e = dict_find(d, key);
    if (!e)
    {
        return false;
    }

    for (int i = e - d->elems; i < d->size - 1; i++)
    {
        d->elems[i] = d->elems[i + 1];
    }
    d->size--;
    return true;
}

bool dict_free(dict *d)
{
    free(d->elems);
    free(d);
    return true;
}

void dict_print(dict *d)
{
    printf("dict: %p\n", d);
    for (int i = 0; i < d->size; i++)
    {
        printf("  %s: %s\n", d->elems[i].key, d->elems[i].value);
    }
    printf("\n");
}

char *dict_get(dict *d, char *key)
{
    dict_elem *e = dict_find(d, key);
    if (!e)
    {
        return NULL;
    }
    return e->value;
}

char *dict_error(int e)
{
    switch (e)
    {
    case DICT_OK:
        return "DICT_OK";
    case DICT_ALLOC_ERROR:
        return "DICT_ALLOC_ERROR";
    case DICT_BAD_POINTER:
        return "DICT_BAD_POINTER";
    case DICT_OTHER_ERROR:
        return "DICT_OTHER_ERROR";
    default:
        return "UNKNOWN_ERROR";
    }
}