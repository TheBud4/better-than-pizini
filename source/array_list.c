#include "array_list.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

void __array_list_drop(array_list_void *const array_list,
                       size_t const item_size,
                       void (*const collector)(void *data),
                       void (*const free)(void *ptr)) {
  if (array_list->__array_list_length == 0)
    return;
  for (size_t index_pos = 0;
       index_pos < array_list->__array_list_length * item_size;
       index_pos += item_size)
    collector(array_list->__array_list_data + index_pos);
  free(array_list->__array_list_data);
  array_list->__array_list_data = NULL;
  array_list->__array_list_length = 0;
}

void *__array_list_index(array_list_void array_list, size_t item_size,
                         size_t index) {
  if (index >= array_list.__array_list_length)
    return NULL;
  return array_list.__array_list_data + item_size * index;
}

bool __array_list_insert(array_list_void *array_list_ref, size_t item_size,
                         size_t index, void *item,
                         void *(*realloc)(void *ptr, size_t size)) {
  void *new_data =
      realloc(array_list_ref->__array_list_data,
              item_size * (array_list_ref->__array_list_length + 1));
  if (new_data == NULL)
    return false;
  void *item_pos = new_data + index * item_size;
  array_list_ref->__array_list_length++;
  array_list_ref->__array_list_data = new_data;
  memmove(item_pos + item_size, item_pos,
          item_size * (array_list_ref->__array_list_length - index - 1));
  memcpy(item_pos, item, item_size);
  return true;
}

void __array_list_remove(array_list_void *array_list_ref, size_t item_size,
                         size_t index, void *item,
                         void *(*realloc)(void *ptr, size_t size)) {
  realloc(array_list_ref->__array_list_data,
          item_size * (array_list_ref->__array_list_length - 1));
  void *item_pos = array_list_ref->__array_list_data + index * item_size;
  array_list_ref->__array_list_length--;
  memmove(item_pos, item_pos + item_size,
          item_size * (array_list_ref->__array_list_length - index));
  memcpy(item, item_pos, item_size);
}