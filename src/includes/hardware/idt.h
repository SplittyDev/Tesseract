#ifndef __idt__
#define __idt__
#include <system/system.h>
#include <system/typedef.h>

#define IDT_ENTRIES 256

typedef struct idt_entry {
  uint16_t  base_low;
  uint16_t  sel;
  uint8_t   zero;
  uint8_t   flags;
  uint16_t  base_high;
} __attribute__((packed)) idtentry_t;

typedef struct idt_pointer {
  uint16_t  limit;
  uint32_t  base;
} __attribute__((packed)) idtptr_t;

void init_idt (void);
stackframe_t *idt_handle_general (stackframe_t *);
extern void idt_load (void);

#endif
