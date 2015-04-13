#include <hardware/pic.h>
#include <io/ports.h>

void pic_remap_master (void);
void pic_remap_slave  (void);
void pic_unmask       (void);

int init_pic (void) {
  pic_remap_master ();
  pic_remap_slave ();
  pic_unmask ();
  return 1;
}

void pic_remap_master (void) {
  outb (0x20, 0x11);
  outb (0x21, 0x20);
  outb (0x21, 0x04);
  outb (0x21, 0x01);
}

void pic_remap_slave (void) {
  outb (0xA0, 0x11);
  outb (0xA1, 0x28);
  outb (0xA1, 0x02);
  outb (0xA1, 0x01);
}

void pic_unmask (void) {
  outb (0x21, 0x0);
  outb (0xA1, 0x0);
}
