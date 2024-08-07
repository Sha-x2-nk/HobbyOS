#include "string.h"

#include <stdint.h> /* uint8_t */
#include <stddef.h> /* size_t */

/* Compares first "size" bytes of str1 and str2 */
int memcmp(const void* str1_ptr, const void* str2_ptr, size_t size) {
    const uint8_t* str1 = (const uint8_t*) str1_ptr;
    const uint8_t* str2 = (const uint8_t*) str2_ptr;

    for (size_t i = 0; i < size; ++i) {
        if (str1[i] < str2[i])
            return -1;
        else if (str2[i] < str1[i])
            return 1;
    }

    return 0;
}