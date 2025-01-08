#include "dict.h"

dict *new_dict()
{
    dict *d = malloc(sizeof(dict));
    if (!d)
        return NULL;
    dict_elem *elems = malloc(DICT_INIT_CAPACITY * sizeof(dict_elem));
    if (!elems)
    {
        free(d);
        return NULL;
    }
    *d = (dict){.elems = elems, .size = 0, .capacity = DICT_INIT_CAPACITY};
    return d;
}

dict_error_code dict_add_capacity(dict *d)
{
    dict_elem *tmp = realloc(d->elems, (d->capacity * 2) * sizeof(dict_elem));
    if (!tmp)
    {
        return DICT_ALLOC_ERROR;
    }
    d->elems = tmp;
    d->capacity *= 2;
    return DICT_OK;
}

dict_error_code dict_add(dict *d, char *key, char *value)
{
    if (!d || !key || !value)
    {
        return DICT_BAD_POINTER;
    }
    if (dict_find(d, key))
    {
        dict_error_code err = dict_del(d, key);
        if (err != DICT_OK)
        {
            return err;
        }
    }
    if (d->size == d->capacity)
    {
        if (dict_add_capacity(d) != DICT_OK)
        {
            return DICT_ALLOC_ERROR;
        }
    }
    strncpy(d->elems[d->size].key, key, DICT_MAX_KEY);
    d->elems[d->size].key[DICT_MAX_KEY - 1] = '\0';
    strncpy(d->elems[d->size].value, value, DICT_MAX_VALUE);
    d->elems[d->size].value[DICT_MAX_VALUE - 1] = '\0';
    d->size++;
    return DICT_OK;
}

dict_elem *dict_find(dict *d, char *key)
{
    for (int i = 0; i < d->size; i++)
    {
        if (strncmp(d->elems[i].key, key, DICT_MAX_KEY) == 0)
        {
            return &d->elems[i];
        }
    }
    return NULL;
}

dict_error_code dict_del(dict *d, char *key)
{
    dict_elem *e = dict_find(d, key);
    if (!e)
    {
        return DICT_NOT_FOUND;
    }

    int index = e - d->elems;
    d->elems[index] = d->elems[d->size - 1];
    d->size--;
    return DICT_OK;
}

dict_error_code dict_free(dict *d)
{
    if (!d)
    {
        return DICT_BAD_POINTER;
    }
    free(d->elems);
    free(d);
    return DICT_OK;
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
    return strdup(e->value);
}

char *dict_error(dict_error_code e)
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