#include <hardware/idt.h>
#include <hardware/isr.h>
#include <system/system.h>
#include <system/typedef.h>
#include <io/memory.h>
#include <io/terminal.h>
#include <io/ports.h>

idtentry_t  idt[IDT_ENTRIES];
idtptr_t    idt_ptr;

void idt_set_gate         (uint8_t, uint32_t, uint16_t, uint8_t);
void idt_set_exceptions   (void);
void idt_set_irqs         (void);
void idt_set_syscalls     (void);
void idt_remap            (void);
void idt_handle_exception (stackframe_t *);
void idt_handle_irq       (stackframe_t *);

void init_idt (void) {
  idt_remap ();

  idt_ptr.limit = (sizeof (idtentry_t) * IDT_ENTRIES) - 1;
  idt_ptr.base  = (uint32_t) &idt;

  idt_set_exceptions ();
  idt_set_irqs ();
  idt_set_syscalls ();

  memset (&idt, 0, sizeof (idtentry_t) * IDT_ENTRIES);

  idt_load ();
}

void idt_set_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_low   = (base)        & 0xFFFF;
  idt[num].base_high  = (base >> 16)  & 0xFFFF;
  idt[num].sel        = (sel);
  idt[num].flags      = (flags);
  idt[num].zero       = 0;
}

void idt_remap (void) {
  outb (0x20, 0x11);
  outb (0xA0, 0x11);
  outb (0x21, 0x20);
  outb (0xA1, 0x28);
  outb (0x21, 0x04);
  outb (0xA1, 0x02);
  outb (0x21, 0x01);
  outb (0xA1, 0x01);
  outb (0x21, 0x0);
  outb (0xA1, 0x0);
}

stackframe_t *idt_handle_general (stackframe_t *frame) {
  if (frame->intr <= 0x1F) {
    idt_handle_exception (frame);
  } else if (frame->intr >= 0x20 && frame->intr <= 0x2F) {
    idt_handle_irq (frame);
    if (frame->intr >= 0x28)
      outb (0xA0, 0x20);
    outb (0x20, 0x20);
  }
  return frame;
}

void idt_handle_exception (stackframe_t *frame) {
  puts ("x");
}

void idt_handle_irq (stackframe_t *frame) {
  puts (".");
}

void idt_set_exceptions (void) {
  idt_set_gate (0x00, (uint32_t) isr0,  0x08, 0x8E);
  idt_set_gate (0x01, (uint32_t) isr1,  0x08, 0x8E);
  idt_set_gate (0x02, (uint32_t) isr2,  0x08, 0x8E);
  idt_set_gate (0x03, (uint32_t) isr3,  0x08, 0x8E);
  idt_set_gate (0x04, (uint32_t) isr4,  0x08, 0x8E);
  idt_set_gate (0x05, (uint32_t) isr5,  0x08, 0x8E);
  idt_set_gate (0x06, (uint32_t) isr6,  0x08, 0x8E);
  idt_set_gate (0x07, (uint32_t) isr7,  0x08, 0x8E);
  idt_set_gate (0x08, (uint32_t) exc8,  0x08, 0x8E);
  idt_set_gate (0x09, (uint32_t) isr9,  0x08, 0x8E);
  idt_set_gate (0x0A, (uint32_t) exc10, 0x08, 0x8E);
  idt_set_gate (0x0B, (uint32_t) exc11, 0x08, 0x8E);
  idt_set_gate (0x0C, (uint32_t) exc12, 0x08, 0x8E);
  idt_set_gate (0x0D, (uint32_t) exc13, 0x08, 0x8E);
  idt_set_gate (0x0E, (uint32_t) exc14, 0x08, 0x8E);
  idt_set_gate (0x0F, (uint32_t) isr15, 0x08, 0x8E);
  idt_set_gate (0x10, (uint32_t) isr16, 0x08, 0x8E);
  idt_set_gate (0x11, (uint32_t) isr17, 0x08, 0x8E);
  idt_set_gate (0x12, (uint32_t) isr18, 0x08, 0x8E);
  idt_set_gate (0x13, (uint32_t) isr19, 0x08, 0x8E);
  idt_set_gate (0x14, (uint32_t) isr20, 0x08, 0x8E);
  idt_set_gate (0x15, (uint32_t) isr21, 0x08, 0x8E);
  idt_set_gate (0x16, (uint32_t) isr22, 0x08, 0x8E);
  idt_set_gate (0x17, (uint32_t) isr23, 0x08, 0x8E);
  idt_set_gate (0x18, (uint32_t) isr24, 0x08, 0x8E);
  idt_set_gate (0x19, (uint32_t) isr25, 0x08, 0x8E);
  idt_set_gate (0x1A, (uint32_t) isr26, 0x08, 0x8E);
  idt_set_gate (0x1B, (uint32_t) isr27, 0x08, 0x8E);
  idt_set_gate (0x1C, (uint32_t) isr28, 0x08, 0x8E);
  idt_set_gate (0x1D, (uint32_t) isr29, 0x08, 0x8E);
  idt_set_gate (0x1E, (uint32_t) isr30, 0x08, 0x8E);
  idt_set_gate (0x1F, (uint32_t) isr31, 0x08, 0x8E);
}

void idt_set_irqs (void) {
  idt_set_gate (0x20, (uint32_t) irq0,  0x08, 0x8E);
  idt_set_gate (0x21, (uint32_t) irq1,  0x08, 0x8E);
  idt_set_gate (0x22, (uint32_t) irq2,  0x08, 0x8E);
  idt_set_gate (0x23, (uint32_t) irq3,  0x08, 0x8E);
  idt_set_gate (0x24, (uint32_t) irq4,  0x08, 0x8E);
  idt_set_gate (0x25, (uint32_t) irq5,  0x08, 0x8E);
  idt_set_gate (0x26, (uint32_t) irq6,  0x08, 0x8E);
  idt_set_gate (0x27, (uint32_t) irq7,  0x08, 0x8E);
  idt_set_gate (0x28, (uint32_t) irq8,  0x08, 0x8E);
  idt_set_gate (0x29, (uint32_t) irq9,  0x08, 0x8E);
  idt_set_gate (0x2A, (uint32_t) irq10, 0x08, 0x8E);
  idt_set_gate (0x2B, (uint32_t) irq11, 0x08, 0x8E);
  idt_set_gate (0x2C, (uint32_t) irq12, 0x08, 0x8E);
  idt_set_gate (0x2D, (uint32_t) irq13, 0x08, 0x8E);
  idt_set_gate (0x2E, (uint32_t) irq14, 0x08, 0x8E);
  idt_set_gate (0x2F, (uint32_t) irq15, 0x08, 0x8E);
}

void idt_set_syscalls (void) {
}
