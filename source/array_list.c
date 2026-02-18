#include "array_list.h"
#include <stddef.h>

void *__array_list_index(array_list_t array_list, size_t index, size_t size) {

  if (index >= array_list.length)
    return NULL;

  return array_list.data + index * size;
}
