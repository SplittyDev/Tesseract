#ifndef __ports__
#define __ports__
#include <system/typedef.h>

static inline uint8_t inb (port_t port) {
  uint8_t ret;
  asm volatile ("inb %1, %0" : "=a" (ret) : "Nd" (port));
  return ret;
}

static inline uint16_t inw (port_t port) {
  uint16_t ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "Nd" (port));
  return ret;
}

static inline uint32_t inl (port_t port) {
  uint32_t ret;
  asm volatile ("inl %1, %0" : "=a" (ret) : "Nd" (port));
  return ret;
}

static inline void outb (port_t port, uint8_t value) {
  asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

static inline void outw (port_t port, uint16_t value) {
  asm volatile ("outw %0, %1" : : "a" (value), "Nd" (port));
}

static inline void outl (port_t port, uint32_t value) {
  asm volatile ("outl %0, %1" : : "a" (value), "Nd" (port));
}

#endif
