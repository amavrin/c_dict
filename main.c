#include "main.h"

int main(void)
{
    dict *d = new_dict();
    if (!d)
    {
        fprintf(stderr, "Failed to create dict\n");
        return 1;
    }
    int err = 0;

    err = dict_add(d, "key1", "value1");
    if (err != DICT_OK)
    {
        fprintf(stderr, "Failed to add key1: %s\n", dict_error(err));
        return 1;
    }

    err = dict_add(d, "key2", "value2");
    if (err != DICT_OK)
    {
        fprintf(stderr, "Failed to add key2: %s\n", dict_error(err));
        return 1;
    }

    err = dict_add(d, "key1", NULL);
    if (err != DICT_BAD_POINTER)
    {
        fprintf(stderr, "error is not DICT_BAD_POINTER but %s", dict_error(err));
        return 1;
    }

    dict_print(d);

    dict_elem *e = dict_find(d, "key1");
    if (!e)
    {
        fprintf(stderr, "Failed to find key1\n");
        return 1;
    }
    printf("key1: %s\n", e->value);

    if (!dict_del(d, "key1"))
    {
        fprintf(stderr, "Failed to delete key1\n");
        return 1;
    }

    dict_print(d);

    char *value = dict_get(d, "key2");
    if (!value)
    {
        fprintf(stderr, "Failed to get value of key2\n");
        return 1;
    }
    printf("key2: %s\n", value);

    char nkey[DICT_MAX_KEY];
    char nvalue[DICT_MAX_VALUE];
    for (int i = 0; i < 100; i++)
    {
        sprintf(nkey, "key%d", i);
        sprintf(nvalue, "value%d", i);
        err = dict_add(d, nkey, nvalue);
        if (err != DICT_OK)
        {
            fprintf(stderr, "Failed to add key:value %s:%s, error: %s\n", nkey, nvalue, dict_error(err));
            return 1;
        }
    }
    for (int i = 0; i < 90; i++)
    {
        sprintf(nkey, "key%d", i);
        if (!dict_del(d, nkey))
        {
            fprintf(stderr, "Failed to delete key: %s\n", nkey);
            return 1;
        }
    }
    dict_print(d);
    for (int i = 0; i < 100; i++)
    {
        sprintf(nkey, "key%d", i);
        sprintf(nvalue, "value%d", i);
        err = dict_add(d, nkey, nvalue);
        if (err != DICT_OK)
        {
            fprintf(stderr, "Failed to add key:value %s:%s, error: %s\n", nkey, nvalue, dict_error(err));
            return 1;
        }
    }
    printf("dict size: %d\ndict capacity: %d\n", d->size, d->capacity);
    if (!dict_free(d))
    {
        fprintf(stderr, "Failed to free dict\n");
        return 1;
    }
}