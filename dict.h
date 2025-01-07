#ifndef DICT_H
#define DICT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DICT_OK 0
#define DICT_ALLOC_ERROR 1
#define DICT_BAD_POINTER 2
#define DICT_OTHER_ERROR 3

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
int dict_add(dict *d, char *key, char *value);
dict_elem *dict_find(dict *d, char *key);
bool dict_del(dict *d, char *key);
void dict_print(dict *d);
bool dict_free(dict *d);
char *dict_get(dict *d, char *key);
char *dict_error(int e);

#endif // DICT_H