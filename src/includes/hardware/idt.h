#ifndef __idt__
#define __idt__

#include <system/system.h>
#include <system/typedef.h>

#define IDT_ENTRIES 256

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_entry idt[IDT_ENTRIES];

void init_idt (void);
void idt_install_handler (int8_t, void (*)(stackframe_t *));
void idt_uninstall_handler (int8_t);

#endif
