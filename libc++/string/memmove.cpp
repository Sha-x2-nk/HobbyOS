#include "cstring"

#include <cstdint> /* uint8_t */
#include <cstddef> /* size_t */

namespace std {

    /* Copies "size" bytes from src to dst and returns pointer to dst (safe checks for memory overlapping) */
    void* memmove(void* dst_ptr, const void* src_ptr, size_t size) {
        uint8_t* dst = static_cast<uint8_t*> (dst_ptr);
        const uint8_t* src = static_cast<const uint8_t*> (src_ptr);

        if (dst < src) {
            for (size_t i = 0; i < size; ++i)
                dst[i] = src[i];
        }
        else {
            for (size_t i = size; i != 0; --i)
                dst[i - 1] = src[i - 1];
        }

        return dst_ptr;
    }

} /* namespace std */