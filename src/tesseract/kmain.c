#include <system/typedef.h>
#include <system/system.h>
#include <io/terminal.h>
#include <hardware/gdt.h>
#include <hardware/idt.h>

void init (void) {
  asm volatile ("cli");
  init_terminal ();
  init_gdt ();
  init_pic ();
  init_idt ();
  asm volatile ("sti");
  puts ("Hello from Tesseract!");
  while (true) {
  }
}
