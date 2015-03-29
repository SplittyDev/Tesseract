#ifndef __memory__
#define __memory__
#include <system/typedef.h>

static inline uintptr_t *memcopy (
  uintptr_t *dest, uintptr_t *src, size_t count) {
  size_t i = 0;
  for (; i < count; i++)
    dest[i] = src[i];
  return dest;
}

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

#endif
