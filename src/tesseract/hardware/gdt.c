#include <hardware/gdt.h>
#include <system/typedef.h>

struct {
  uint16_t limit;
  void     *pointer;
} __attribute__((packed)) gdt_ptr = {
  .limit    = GDT_ENTRIES * 8 - 1,
  .pointer  = gdt,
};

void gdt_create_descriptor (size_t, uint32_t, uint32_t, uint16_t);

void init_gdt (void) {
  gdt_create_descriptor (0, 0, 0, 0);
  gdt_create_descriptor (1, 0, 0x000FFFFF, (GDT_CODE_PL0));
  gdt_create_descriptor (2, 0, 0x000FFFFF, (GDT_DATA_PL0));
  gdt_create_descriptor (3, 0, 0x000FFFFF, (GDT_CODE_PL3));
  gdt_create_descriptor (4, 0, 0x000FFFFF, (GDT_DATA_PL3));
  // -> TSS
  asm volatile ("lgdt %0" : : "m" (gdt_ptr));
  gdt_flush ();
}

void gdt_create_descriptor
  (size_t i, uint32_t base, uint32_t limit, uint16_t flags) {
    uint64_t descriptor;
    descriptor   = limit          & 0x000F0000;
    descriptor  |= (flags <<  8)  & 0x00F0FF00;
    descriptor  |= (base  >> 16)  & 0x000000FF;
    descriptor  |= base           & 0xFF000000;
    descriptor <<= 32;
    descriptor  |= base   << 16;
    descriptor  |= limit          & 0x0000FFFF;
    gdt[i] = descriptor;
}
