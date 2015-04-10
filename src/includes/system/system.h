#ifndef __system__
#define __system__
#include <system/typedef.h>

#define IRQ_ON  asm volatile ("sti")
#define IRQ_OFF asm volatile ("cli")

typedef struct stackframe {
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t intr, error;
  uint32_t eip, cs, eflags, useresp, ss;
} stackframe_t;

static const uint8_t *exception_messages[] =
{
	"DIVIDE BY ZERO EXCEPTION\n",              // 0x00
	"DEBUG EXCEPTION\n",                       // 0x01
	"NON MASKABLE INTERRUPT EXCEPTION\n",      // 0x02
	"BREAKPOINT EXCEPTION\n",                  // 0x03
	"INTO DETECTED OVERFLOW EXCEPTION\n",      // 0x04
	"OUT OF BOUNDS EXCEPTION\n",               // 0x05
	"INVALID OPCODE EXCEPTION\n",              // 0x06
	"NO COPROCESSOR EXCEPTION\n",              // 0x07
	"DOUBLE FAULT EXCEPTION\n",                // 0x08
	"COPROCESSOR SEGMENT OVERRUN EXCEPTION\n", // 0x09
	"BAD TSS EXCEPTION\n",                     // 0x0A
	"SEGMENT NOT PRESENT EXCEPTION\n",         // 0x0B
	"STACK FAULT EXCEPTION\n",                 // 0x0C
	"GENERAL PROTECTION FAULT EXCEPTION\n",    // 0x0D
	"PAGE FAULT EXCEPTION\n",                  // 0x0E
	"UNKNOWN INTERRUPT EXCEPTION\n",           // 0x0F
	"COPROCESSOR FAULT EXCEPTION\n",           // 0x10
	"ALIGNMENT CHECK EXCEPTION\n",             // 0x11
  "MACHINE CHECK EXCEPTION\n",               // 0x12
};

#endif
