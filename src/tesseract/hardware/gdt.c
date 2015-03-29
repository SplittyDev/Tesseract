#include <hardware/gdt.h>
#include <system/typedef.h>

gdt_entry   gdt[GDT_ENTRIES];
gdt_pointer gdt_ptr;

void gdt_set_gate (uint8_t, uint32_t, uint32_t, uint8_t, uint8_t);

void init_gdt (void) {
  gdt_ptr.limit = (sizeof (gdt_entry) * GDT_ENTRIES) - 1;
  gdt_ptr.base  = (uint32_t) &gdt;

  // Null descriptor
  gdt_set_gate (0, 0, 0, 0, 0);

  // Kernel code segment
  gdt_set_gate (1, 0, GDT_LIMIT_4G, 0x9A, 0xCF);

  // Kernel data segment
  gdt_set_gate (2, 0, GDT_LIMIT_4G, 0x92, 0xCF);

  // Flush GDT
  gdt_flush ();
}

void gdt_set_gate
  (uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
  gdt[num].base_low     = (base)        & 0xFFFF;
  gdt[num].base_middle  = (base >> 16)  & 0xFF;
  gdt[num].base_high    = (base >> 24)  & 0xFF;
  gdt[num].limit_low    = (limit)       & 0xFFFF;
  gdt[num].granularity  = (limit >> 16) & 0x0F;
  gdt[num].granularity |= (gran)        & 0xF0;
  gdt[num].access       = (access);
}
