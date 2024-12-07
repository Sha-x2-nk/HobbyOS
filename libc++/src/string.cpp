/* 
  Copyright 2024 Shashank Rajora
  All rights reserved. 
*/
#include "cstring"

#include <cstdint>
#include <cstddef>

namespace std {

/* Compares first n bytes of str1 and str2 */
int memcmp(const void* str1_ptr, const void* str2_ptr, size_t n) {
  const uint8_t* str1 = static_cast<const uint8_t*> (str1_ptr);
  const uint8_t* str2 = static_cast<const uint8_t*> (str2_ptr);

  for (size_t i = 0; i < n; ++i) {
    if (str1[i] < str2[i]) {
      return -1;
    } else if (str2[i] < str1[i]) {
      return 1;
    }
  }

  return 0;
}

/* 
  Copies n bytes from src to dst and returns
  pointer to dst (assumes non-overlapping memory) 
*/
void* memcpy(void* __restrict__ dst_ptr,
    const void* __restrict__ src_ptr, size_t n) {
  uint8_t* dst = static_cast<uint8_t*> (dst_ptr);
  const uint8_t* src = static_cast<const uint8_t*> (src_ptr);

  for (size_t i = 0; i < n; ++i)
    dst[i] = src[i];

  return dst_ptr;
}

/* 
  Copies n bytes from src to dst and returns pointer
  to dst (safe checks for memory overlapping) 
*/
void* memmove(void* dst_ptr, const void* src_ptr, size_t n) {
    uint8_t* dst = static_cast<uint8_t*> (dst_ptr);
  const uint8_t* src = static_cast<const uint8_t*> (src_ptr);

  if (dst < src) {
    for (size_t i = 0; i < n; ++i)
      dst[i] = src[i];
  } else {
    for (size_t i = n; i != 0; --i)
      dst[i - 1] = src[i - 1];
  }

  return dst_ptr;
}

/* 
  Copies val (1 byte) to the first n bytes
  in src and returns pointer to src 
*/
void* memset(void* src_ptr, int val, size_t n) {
  uint8_t* src = static_cast<uint8_t*> (src_ptr);

  for (size_t i = 0; i < n; ++i)
    src[i] = static_cast<uint8_t> (val);

  return src_ptr;
}

/* 
  Computes the length of the string src up to 
  but not including the terminal NULL character 
*/
size_t strlen(const char* src_ptr) {
  size_t len = 0;

  while (src_ptr[len])
    ++len;

  return len;
}

} /* namespace std */
