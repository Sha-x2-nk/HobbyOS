#include "string.h"

#include <stdint.h> /* uint8_t */
#include <stddef.h> /* size_t */

/* Copies val (1 byte) to the first "size" bytes in src and returns pointer to src */
void* memset(void* src_ptr, int val, size_t size) {
    uint8_t* src = (uint8_t*) src_ptr;

    for(size_t i = 0; i < size; ++i)
        src[i] = (uint8_t) val;

    return src_ptr;
}
