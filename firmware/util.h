#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

/**
 * @brief cmp_const_time compare two arrays in constant time (this avoids timing attacks)
 * @param a first array
 * @param b second array
 * @param size size in bytes of the two arrays
 * @return 0 if and only if the two arrays match
 */
char cmp_const_time(void *a, void *b, uint8_t size);


#endif // UTIL_H
