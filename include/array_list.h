#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stddef.h>

typedef struct array_list array_list_t;

array_list_t array_list_make();
void array_list_drop(array_list_t *const array_list,
                     void (*dropper)(void *data));

#define array_list_index(T, array_list, index)                                 \
  ((T *)__array_list_index(array_list, index, sizeof(T)))
void *__array_list_index(const array_list_t array_list, const size_t index,
                         const size_t size);

struct array_list {
  size_t length;
  void *data;
};

#endif // ARRAY_LIST_H