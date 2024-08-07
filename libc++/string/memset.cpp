#include "cstring"

#include <cstdint> /* uint8_t */
#include <cstddef> /* size_t */

namespace std {

    /* Copies val (1 byte) to the first "size" bytes in src and returns pointer to src */
    void* memset(void* src_ptr, int val, size_t size) {
        uint8_t* src = static_cast<uint8_t*> (src_ptr);

        for(size_t i = 0; i < size; ++i)
            src[i] = static_cast<uint8_t> (val);

        return src_ptr;
    }

} /* namespace std */