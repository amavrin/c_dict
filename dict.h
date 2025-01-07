#ifndef DICT_H
#define DICT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dict_elem
{
    char *key;
    char *value;
} dict_elem;

typedef struct dict
{
    dict_elem *elems;
    int size;
} dict;

dict *new_dict();
bool dict_add(dict *d, char *key, char *value);
dict_elem *dict_find(dict *d, char *key);
bool dict_del(dict *d, char *key);
void dict_print(dict *d);
bool dict_free(dict *d);

#endif // DICT_H