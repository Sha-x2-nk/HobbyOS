#include "string.h"

#include <stdint.h> /* uint8_t */
#include <stddef.h> /* size_t */

/* Computes the length of the string src up to but not including the terminal NULL character */
size_t strlen(const char* src_ptr) {
    size_t len = 0;

    while (src_ptr[len])
        ++len;

    return len;
}