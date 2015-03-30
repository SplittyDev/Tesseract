#ifndef __idt__
#define __idt__
#include <system/system.h>
#include <system/typedef.h>

#define IDT_ENTRIES 256

struct idt_entry {
  uint16_t  base_low;
  uint16_t  sel;
  uint8_t   zero;
  uint8_t   flags;
  uint16_t  base_high;
} __attribute__((packed));

struct idt_entry idt[IDT_ENTRIES];

void init_idt (void);
stackframe_t *idt_handle_general (stackframe_t *);

#endif
