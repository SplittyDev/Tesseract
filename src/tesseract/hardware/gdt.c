#include <hardware/gdt.h>
#include <system/typedef.h>

uint64_t    gdt[GDT_ENTRIES];
gdt_ptr_t   gdt_ptr;

void gdt_set_gate (uint8_t, uint32_t, uint32_t, int32_t);
void gdt_set_ring0_gate (uint8_t, uint32_t, uint32_t, int32_t);
void gdt_set_ring3_gate (uint8_t, uint32_t, uint32_t, int32_t);

void init_gdt (void) {
  gdt_ptr.limit = GDT_ENTRIES * 8 - 1;
  gdt_ptr.base  = &gdt;

  // Null descriptor
  gdt_set_gate (0, 0, 0, 0);

  // Kernel code segment
  gdt_set_ring0_gate (1, 0, 0xFFFFF,
    GDT_SEGMENT | GDT_32_BIT | GDT_CODESEG | GDT_4K_GRAN | GDT_PRESENT);

  // Kenel data segment
  gdt_set_ring0_gate (2, 0, 0xFFFFF,
    GDT_SEGMENT | GDT_32_BIT | GDT_DATASEG | GDT_4K_GRAN | GDT_PRESENT);

  // User code segment
  gdt_set_ring3_gate (3, 0, 0xFFFFF,
    GDT_SEGMENT | GDT_32_BIT | GDT_CODESEG | GDT_4K_GRAN | GDT_PRESENT);

  // User data segment
  gdt_set_ring3_gate (4, 0, 0xFFFFF,
    GDT_SEGMENT | GDT_32_BIT | GDT_CODESEG | GDT_4K_GRAN | GDT_PRESENT);

  // TSS
  //gdt_set_gate (5, 0, 0xFFFFF, GDT_TSS | GDT_RING3 | GDT_PRESENT);

  // Load GDT
  asm volatile ("lgdt %0" : : "m" (gdt_ptr));

  // Flush GDT
  gdt_flush ();
}

void gdt_set_ring0_gate (uint8_t i, uint32_t b, uint32_t l, int32_t f) {
  gdt_set_gate (i, b, l, f | GDT_RING0);
}

void gdt_set_ring3_gate (uint8_t i, uint32_t b, uint32_t l, int32_t f) {
  gdt_set_gate (i, b, l, f | GDT_RING3);
}

void gdt_set_gate (uint8_t num, uint32_t base, uint32_t limit, int32_t flags) {
  gdt[num]  = limit           & 0xFFFFLL;
  gdt[num] |= (base           & 0xFFFFFFLL) << 16;
  gdt[num] |= (flags          & 0xFFLL)     << 40;
  gdt[num] |= ((limit >> 16)  & 0xFLL)      << 48;
  gdt[num] |= ((flags >> 8)   & 0xFFLL)     << 52;
  gdt[num] |= ((base  >> 24)  & 0xFFLL)     << 56;
}
