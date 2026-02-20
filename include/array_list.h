#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

#define array_list_t(T) struct { size_t __array_list_length; T* __array_list_data; }
typedef array_list_t(void) array_list_void;

#define array_list_item_type(array_list) __typeof__(*(array_list).__array_list_data)
#define array_list_item_size(array_list) sizeof(*(array_list).__array_list_data)
#define array_list_length(array_list) ((array_list).__array_list_length)

#define array_list_make(T) {0, 0}
#define array_list_drop(array_list_ref, collector, free) __array_list_drop((array_list_void*) (array_list_ref), array_list_item_size(*array_list_ref), collector, free)

#define array_list_cast(T, array_list) = (*(array_list_t(T)*) utils_type_erase(array_list))
#define array_list_copy(array_list_1_ref, array_list_2) \
    (*(array_list_void*) &(array_list_1_ref) = (array_list_void) {(array_list_2).__array_list_length, (array_list_2).__array_list_data})

#define array_list_index(array_list, index) \
    ((__typeof__((array_list).__array_list_data)) __array_list_index(*(array_list_void*) &array_list, array_list_item_size(array_list), index))

#define array_list_insert(array_list_ref, index, item, realloc) \
    __array_list_insert((array_list_void*)(array_list_ref), array_list_item_size(*(array_list_ref)), index, utils_type_erase(item), realloc)
#define array_list_push_back(array_list_ref, item, realloc) ({ \
        __typeof__(array_list_ref) array_list_ref_val = (array_list_ref); \
        array_list_insert(array_list_ref_val, array_list_length(*array_list_ref_val), item, realloc); \
    })
#define array_list_push_front(array_list_ref, item, realloc) \
    __array_list_insert((array_list_void*)(array_list_ref), array_list_item_size(*(array_list_ref)), 0, utils_type_erase(item), realloc)

#define array_list_remove(array_list_ref, index, realloc) ({ \
        __typeof__(*(array_list_ref)->__array_list_data) item; \
        __array_list_remove((array_list_void*) array_list_ref, sizeof(item), index, &(item), realloc); \
        item; \
    })
#define array_list_pull_back(array_list_ref, realloc) ({ \
        __typeof__(array_list_ref) array_list_ref_val = (array_list_ref); \
        array_list_remove(array_list_ref_val, array_list_length(*array_list_ref_val) - 1, realloc); \
    })
#define array_list_pull_front(array_list_ref, realloc) ({ \
        __typeof__(array_list_ref) array_list_ref_val = (array_list_ref); \
        array_list_remove(array_list_ref_val, 0, realloc); \
    })

void __array_list_drop(array_list_void *const array_list, size_t const item_size, void (*const collector)(void *data), void (*const free)(void *ptr));
void* __array_list_index(array_list_void array_list, size_t item_size, size_t index);
bool __array_list_insert(array_list_void *array_list, size_t item_size, size_t index, void* item, void* (*realloc)(void *ptr, size_t size));
void __array_list_remove(array_list_void *array_list, size_t item_size, size_t index, void* item, void* (*realloc)(void *ptr, size_t size));

#endif // ARRAY_LIST_H