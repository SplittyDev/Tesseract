#ifndef __system__
#define __system__
#include <system/typedef.h>

typedef struct stackframe {
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t intr, error;
  uint32_t eip, cs, eflags, useresp, ss;
} stackframe_t;

#endif
