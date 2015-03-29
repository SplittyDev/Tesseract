#ifndef __gdt__
#define __gdt__
#include <system/typedef.h>

#define GDT_ENTRIES 5

#define GDT_DATASEG 0x02
#define GDT_CODESEG 0x0a
#define GDT_TSS     0x09

#define GDT_SEGMENT 0x10
#define GDT_RING0   0x00
#define GDT_RING3   0x60
#define GDT_PRESENT 0x80

#define GDT_4K_GRAN 0x800
#define GDT_32_BIT  0x400

typedef struct gdt_pointer {
  uint16_t  limit;
  void      *base;
} __attribute__((packed)) gdt_ptr_t;

void init_gdt (void);
extern void gdt_flush (void);

#endif
