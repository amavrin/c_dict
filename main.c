#include "main.h"

int main(void)
{
    dict *d = new_dict();
    if (!dict_add(d, "key1", "value1"))
    {
        printf("Failed to add key1\n");
        return 1;
    }
    if (!dict_add(d, "key2", "value2"))
    {
        printf("Failed to add key2\n");
        return 1;
    }

    dict_print(d);

    dict_elem *e = dict_find(d, "key1");
    if (!e)
    {
        printf("Failed to find key1\n");
        return 1;
    }
    printf("key1: %s\n", e->value);

    if (!dict_del(d, "key1"))
    {
        printf("Failed to delete key1\n");
        return 1;
    }

    dict_print(d);

    if (!dict_free(d))
    {
        printf("Failed to free dict\n");
        return 1;
    }
}