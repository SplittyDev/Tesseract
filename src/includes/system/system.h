#ifndef __system__
#define __system__
#include <system/typedef.h>

#define ENABLE_IRQS   asm volatile ("cli");
#define DISABLE_IRQS  asm volatile ("sti");
#define PAUSE         asm volatile ("hlt");
#define HALT          asm volatile ("hlt");

typedef struct stackframe {
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t intr, err;
  uint32_t eip, cs, eflags, useresp, ss;
} stackframe_t;

#endif
