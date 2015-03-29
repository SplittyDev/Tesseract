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
inline void idt_load      (void);

uint8_t *exception_messages[] =
{
	"*** DIVIDE BY ZERO EXCEPTION\n",              // 0x00
	"*** DEBUG EXCEPTION\n",                       // 0x01
	"*** NON MASKABLE INTERRUPT EXCEPTION\n",      // 0x02
	"*** BREAKPOINT EXCEPTION\n",                  // 0x03
	"*** INTO DETECTED OVERFLOW EXCEPTION\n",      // 0x04
	"*** OUT OF BOUNDS EXCEPTION\n",               // 0x05
	"*** INVALID OPCODE EXCEPTION\n",              // 0x06
	"*** NO COPROCESSOR EXCEPTION\n",              // 0x07
	"*** DOUBLE FAULT EXCEPTION\n",                // 0x08
	"*** COPROCESSOR SEGMENT OVERRUN EXCEPTION\n", // 0x09
	"*** BAD TSS EXCEPTION\n",                     // 0x0A
	"*** SEGMENT NOT PRESENT EXCEPTION\n",         // 0x0B
	"*** STACK FAULT EXCEPTION\n",                 // 0x0C
	"*** GENERAL PROTECTION FAULT EXCEPTION\n",    // 0x0D
	"*** PAGE FAULT EXCEPTION\n",                  // 0x0E
	"*** UNKNOWN INTERRUPT EXCEPTION\n",           // 0x0F
	"*** COPROCESSOR FAULT EXCEPTION\n",           // 0x10
	"*** ALIGNMENT CHECK EXCEPTION\n",             // 0x11
  "*** MACHINE CHECK EXCEPTION\n",               // 0x12
};

void init_idt (void) {
  idt_remap ();

  idt_ptr.limit = (sizeof (idtentry_t) * IDT_ENTRIES) - 1;
  idt_ptr.base  = &idt;

  idt_set_exceptions ();
  idt_set_irqs ();
  idt_set_syscalls ();

  memset (&idt, 0, sizeof (idtentry_t) * IDT_ENTRIES);
  idt_load ();
}

inline void idt_load (void) {
  asm volatile ("lidt %0" : : "m" (idt_ptr));
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
  stackframe_t *newframe = frame;

  // Exceptions
  if (frame->intr <= 0x1F) {
    idt_handle_exception (frame);
  }

  // IRQs
  if (frame->intr >= 0x20 && frame->intr <= 0x2F) {
    idt_handle_irq (frame);

    // EOI to slave controller
    if (frame->intr >= 0x28)
      outb (0xA0, 0x20);

    // EOI to master controller
    outb (0x20, 0x20);
  }

  return newframe;
}

void idt_handle_exception (stackframe_t *frame) {
  puts (exception_messages[frame->intr]);
  while (true) {
    asm volatile ("cli; hlt");
  }
}

void idt_handle_irq (stackframe_t *frame) {
  puts (".");
}

void idt_set_exceptions (void) {
  idt_set_gate (0x00, (unsigned) isr0,  0x08, 0x8E);
  idt_set_gate (0x01, (unsigned) isr1,  0x08, 0x8E);
  idt_set_gate (0x02, (unsigned) isr2,  0x08, 0x8E);
  idt_set_gate (0x03, (unsigned) isr3,  0x08, 0x8E);
  idt_set_gate (0x04, (unsigned) isr4,  0x08, 0x8E);
  idt_set_gate (0x05, (unsigned) isr5,  0x08, 0x8E);
  idt_set_gate (0x06, (unsigned) isr6,  0x08, 0x8E);
  idt_set_gate (0x07, (unsigned) isr7,  0x08, 0x8E);
  idt_set_gate (0x08, (unsigned) exc8,  0x08, 0x8E);
  idt_set_gate (0x09, (unsigned) isr9,  0x08, 0x8E);
  idt_set_gate (0x0A, (unsigned) exc10, 0x08, 0x8E);
  idt_set_gate (0x0B, (unsigned) exc11, 0x08, 0x8E);
  idt_set_gate (0x0C, (unsigned) exc12, 0x08, 0x8E);
  idt_set_gate (0x0D, (unsigned) exc13, 0x08, 0x8E);
  idt_set_gate (0x0E, (unsigned) exc14, 0x08, 0x8E);
  idt_set_gate (0x0F, (unsigned) isr15, 0x08, 0x8E);
  idt_set_gate (0x10, (unsigned) isr16, 0x08, 0x8E);
  idt_set_gate (0x11, (unsigned) isr17, 0x08, 0x8E);
  idt_set_gate (0x12, (unsigned) isr18, 0x08, 0x8E);
  idt_set_gate (0x13, (unsigned) isr19, 0x08, 0x8E);
  idt_set_gate (0x14, (unsigned) isr20, 0x08, 0x8E);
  idt_set_gate (0x15, (unsigned) isr21, 0x08, 0x8E);
  idt_set_gate (0x16, (unsigned) isr22, 0x08, 0x8E);
  idt_set_gate (0x17, (unsigned) isr23, 0x08, 0x8E);
  idt_set_gate (0x18, (unsigned) isr24, 0x08, 0x8E);
  idt_set_gate (0x19, (unsigned) isr25, 0x08, 0x8E);
  idt_set_gate (0x1A, (unsigned) isr26, 0x08, 0x8E);
  idt_set_gate (0x1B, (unsigned) isr27, 0x08, 0x8E);
  idt_set_gate (0x1C, (unsigned) isr28, 0x08, 0x8E);
  idt_set_gate (0x1D, (unsigned) isr29, 0x08, 0x8E);
  idt_set_gate (0x1E, (unsigned) isr30, 0x08, 0x8E);
  idt_set_gate (0x1F, (unsigned) isr31, 0x08, 0x8E);
}

void idt_set_irqs (void) {
  idt_set_gate (0x20, (unsigned) irq0,  0x08, 0x8E);
  idt_set_gate (0x21, (unsigned) irq1,  0x08, 0x8E);
  idt_set_gate (0x22, (unsigned) irq2,  0x08, 0x8E);
  idt_set_gate (0x23, (unsigned) irq3,  0x08, 0x8E);
  idt_set_gate (0x24, (unsigned) irq4,  0x08, 0x8E);
  idt_set_gate (0x25, (unsigned) irq5,  0x08, 0x8E);
  idt_set_gate (0x26, (unsigned) irq6,  0x08, 0x8E);
  idt_set_gate (0x27, (unsigned) irq7,  0x08, 0x8E);
  idt_set_gate (0x28, (unsigned) irq8,  0x08, 0x8E);
  idt_set_gate (0x29, (unsigned) irq9,  0x08, 0x8E);
  idt_set_gate (0x2A, (unsigned) irq10, 0x08, 0x8E);
  idt_set_gate (0x2B, (unsigned) irq11, 0x08, 0x8E);
  idt_set_gate (0x2C, (unsigned) irq12, 0x08, 0x8E);
  idt_set_gate (0x2D, (unsigned) irq13, 0x08, 0x8E);
  idt_set_gate (0x2E, (unsigned) irq14, 0x08, 0x8E);
  idt_set_gate (0x2F, (unsigned) irq15, 0x08, 0x8E);
}

void idt_set_syscalls (void) {
}
