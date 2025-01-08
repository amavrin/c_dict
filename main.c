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

    if (!dict_free(d))
    {
        fprintf(stderr, "Failed to free dict\n");
        return 1;
    }
}