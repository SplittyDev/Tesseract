#ifndef __gdt__
#define __gdt__
#include <system/typedef.h>

#define GDT_ENTRIES   3
#define GDT_LIMIT_4G  0xFFFFFFFF

typedef struct gdt_entry {
  uint16_t  limit_low;
  uint16_t  base_low;
  uint8_t   base_middle;
  uint8_t   access;
  uint8_t   granularity;
  uint8_t   base_high;
} __attribute__((packed)) gdt_entry;

typedef struct gdt_pointer {
  uint16_t  limit;
  uint32_t  base;
} __attribute__((packed)) gdt_pointer;

void init_gdt (void);
extern void gdt_flush (void);

#endif
