#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <stddef.h> /* size_t */

/* Compares first n bytes of str1 and str2 */
int memcmp(const void* str1, const void* str2, size_t n);

/* Copies n bytes from src to dst and returns pointer to dst (assumes non-overlapping memory) */
void* memcpy(void* __restrict__ dst, const void* __restrict__ src, size_t n);

/* Copies n bytes from src to dst and returns pointer to dst (safe checks for memory overlapping) */
void* memmove(void* dst, const void* src, size_t n);

/* Copies val (1 byte) to the first n bytes in src and returns pointer to src */
void* memset(void* src, int val, size_t n);

/* Computes the length of the string src up to but not including the terminal NULL character */
size_t strlen(const char* src);

#endif