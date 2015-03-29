#include <system/typedef.h>
#include <system/system.h>
#include <io/terminal.h>
#include <hardware/gdt.h>
#include <hardware/idt.h>

void init (void) {
  init_terminal ();
  init_gdt ();
  init_idt ();
  asm volatile ("sti");
  puts ("Hello from Tesseract!");
  while (true) {
    asm volatile ("hlt");
  }
}
