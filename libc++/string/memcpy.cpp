#include "cstring"

#include <cstdint> /* uint8_t */
#include <cstddef> /* size_t */

namespace std {

    /* Copies "size" bytes from src to dst and returns pointer to dst (assumes non-overlapping memory) */
    void* memcpy(void* __restrict__ dst_ptr, const void* __restrict__ src_ptr, size_t size) {
        uint8_t* dst = static_cast<uint8_t*> (dst_ptr);
        const uint8_t* src = static_cast<const uint8_t*> (src_ptr);

        for(size_t i = 0; i < size; ++i)
            dst[i] = src[i];

        return dst_ptr;
    }

} /* namespace std */