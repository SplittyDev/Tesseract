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

static inline uint8_t *memset
  (uint8_t *dest, uint8_t value, size_t count) {
  size_t i = 0;
  for (; i < count; i++)
    dest[i] = value;
  return dest;
}

static inline uint16_t *memsetw
  (uint16_t *dest, uint16_t value, size_t count) {
  size_t i = 0;
  for (; i < count; i++)
    dest[i] = value;
  return dest;
}

#endif
