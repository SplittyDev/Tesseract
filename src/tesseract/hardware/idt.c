#include <hardware/idt.h>
#include <hardware/isr.h>
#include <system/system.h>
#include <system/typedef.h>
#include <io/memory.h>
#include <io/terminal.h>
#include <io/ports.h>

struct {
    uint16_t	limit;
    void 			*pointer;
} __attribute__((packed)) idt_ptr = {
    .limit		= (sizeof (struct idt_entry) * 256) - 1,
    .pointer	= &idt,
};

void idt_load (void);
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void idt_handle_irq (stackframe_t *);
void idt_handle_syscall (stackframe_t *);
void idt_handle_general (stackframe_t *);
void idt_handle_exception (stackframe_t *);

void init_idt (void) {

  // Clear IDT
  memset ((void *)&idt, 0, sizeof(struct idt_entry) * 256);

  // Exceptions
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

	// IRQs
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

  // Load IDT
  idt_load ();
}

void idt_set_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_lo  = base         & 0xFFFF;
  idt[num].base_hi  = (base >> 16) & 0xFFFF;
  idt[num].sel      = sel;
  idt[num].zero     = 0;
  idt[num].flags    = flags;
}

void idt_load (void) {
  asm volatile ("lidt %0" : : "m" (idt_ptr));
}

void *irq_handlers[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

void idt_install_handler (int8_t irq, void (*handler)(stackframe_t *frame)) {
  irq_handlers[irq] = handler;
  puts ("Installed IRQ handler\n");
  //uint8_t buf[13];
  //puts (itoa (irq, buf));
}

void idt_uninstall_handler (int8_t irq) {
  irq_handlers[irq] = 0;
}

void idt_handle_exception (stackframe_t *frame) {
  // Print exception message
  puts (exception_messages[frame->intr]);

  /*
  // Print debug information
  uint8_t buf[13];
  puts ("[CPU State]");
  puts ("\nGS: ");      puts (itoa (frame->gs,      buf));
  puts ("\t\tFS: ");    puts (itoa (frame->fs,      buf));
  puts ("\t\tES: ");    puts (itoa (frame->es,      buf));
  puts ("\nDS: ");      puts (itoa (frame->ds,      buf));
  puts ("\t\tEDI: ");   puts (itoa (frame->edi,     buf));
  puts ("\t\tESI: ");   puts (itoa (frame->esi,     buf));
  puts ("\nEBP: ");     puts (itoa (frame->ebp,     buf));
  puts ("\t\tESP: ");   puts (itoa (frame->esp,     buf));
  puts ("\tEBX: ");     puts (itoa (frame->ebx,     buf));
  puts ("\nEDX: ");     puts (itoa (frame->edx,     buf));
  puts ("\t\tECX: ");   puts (itoa (frame->ecx,     buf));
  puts ("\tEAX: ");     puts (itoa (frame->eax,     buf));
  puts ("\nEIP: ");     puts (itoa (frame->eip,     buf));
  puts ("\tCS: ");      puts (itoa (frame->cs,      buf));
  puts ("\t\tSS: ");    puts (itoa (frame->ss,      buf));
  puts ("\nEFLAGS: ");  puts (itoa (frame->eflags,  buf));
  puts ("\tUSERESP: "); puts (itoa (frame->useresp, buf));
  */

  // Halt
  while (true) {
    asm ("cli; hlt");
  }
}

void idt_handle_irq (stackframe_t *frame) {

  // Blank IRQ handler
  void (*handler)(stackframe_t *frame);

  // Set our handler to the actual IRQ handler
  handler = irq_handlers[frame->intr - 32];

  // Call the handler
  if (handler)
    handler (frame);
}

void idt_handle_syscall (stackframe_t *frame) {
}

void idt_handle_general (stackframe_t *frame) {

  // Exceptions
  if (frame->intr <= 0x1F) {

    // Call exception handler
    idt_handle_exception (frame);
  }

  // IRQs
  if (frame->intr >= 0x20 && frame->intr <= 0x2F) {

    // Call IRQ handler
    idt_handle_irq (frame);

    // Send EOI to slave interrupt controller
    if (frame->intr >= 0x28) {
      outb (0xA0, 0x20);
    }

    // Send EOI to master interrupt controller
    outb (0x20, 0x20);
  }
}
