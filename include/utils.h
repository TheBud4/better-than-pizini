#ifndef UTILS_H
#define UTILS_H

#define utils_type_erase(value) ((void*) &(__typeof__(value)){value})
#define utils_type_bitcast(T, value) (*(T*) &(__typeof__(value)){value})

#endif // UTILS_H