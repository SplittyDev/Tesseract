#include <system/multiboot.h>
#include <system/typedef.h>
#include <system/system.h>
#include <system/kheap.h>
#include <io/terminal.h>
#include <hardware/gdt.h>
#include <hardware/pic.h>
#include <hardware/idt.h>
#include <hardware/rtc.h>

void main (void);

void invoke (char *msg, int (*func)()) {
  printf ("%s %s\n", msg, func () ? "OK" : "FAIL");
}

void init (multiboot_info_t *mbootinfo) {
  void *kheap = (uint32_t *)(mbootinfo->mods_addr + 4);
  IRQ_OFF;
  init_kheap (kheap, 4096);
  init_terminal ();
  init_gdt ();
  init_pic ();
  init_idt ();
  init_rtc ();
  printf ("Heap, GDT, PIC, IDT and RTC initialized.\n");
  printf ("Gathering video information form multiboot header...\n");
  printf ("Framebuffer width: %d\n", mbootinfo->framebuffer_width);
  printf ("Framebuffer height: %d\n", mbootinfo->framebuffer_height);
  IRQ_ON;
  main ();
}

void main (void) {
  printf ("Tesseract booted.\n");
  date_t date = rtc_get_date ();
  printf ("%s, the %dth of %s %d", DAY[date.dow-1], date.d, MONTH[date.M-1], date.Y);
  while (true) {
  }
}
