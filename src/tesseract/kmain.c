#include <system/typedef.h>
#include <system/system.h>
#include <io/terminal.h>
#include <hardware/gdt.h>
#include <hardware/idt.h>

void init (void) {
  IRQ_OFF;
  init_terminal ();
  init_gdt ();
  init_pic ();
  init_idt ();
  IRQ_ON;
  printf ("Tesseract");
  while (true) {
    
  }
}
