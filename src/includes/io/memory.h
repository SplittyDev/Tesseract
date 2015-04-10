#ifndef __memory__
#define __memory__
#include <system/typedef.h>

static inline void *memcpy (void *dest, void *src, size_t size) {
  asm volatile ("cld");
  asm volatile ("rep movsb" : "+c" (size), "+S" (src), "+D" (dest) :: "memory");
}

static inline void *memset (void *b, int val, size_t size) {
  asm volatile ("cld");
  asm volatile ("rep stosb" : "+c" (size), "+D" (b) : "a" (val) : "memory");
  return b;
}

static inline uintptr_t *memsetw (uintptr_t *ptr, uint8_t val, size_t size) {
  int i = 0;
  for (; i < size; ++i) {
    ptr[i] = val;
  }
  return ptr;
}

/*

static inline void *memset (void *dest, uint8_t value, size_t size) {
  if (size) {
    int8_t *d = dest;
    do {
      *d++ = value;
    } while (--size);
  }
  return dest;
}

static inline void *memsetw (void *dest, uint16_t value, size_t size) {
  if (size) {
    int8_t *d = dest;
    do {
      *d++ = value;
    } while (--size);
  }
  return dest;
}

static inline uintptr_t *memcpy (
  uintptr_t *dest, uintptr_t *src, size_t count) {
  size_t i = 0;
  for (; i < count; i++)
    dest[i] = src[i];
  return dest;
}

*/

#endif
