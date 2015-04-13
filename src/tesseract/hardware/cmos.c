#include <system/typedef.h>
#include <hardware/cmos.h>
#include <io/ports.h>

uint8_t cmos_read (uint8_t offset) {
  uint8_t tmp = inb (0x70);
  outb (0x70, (tmp & 0x80) | (offset & 0x7F));
  return inb (0x71);
}

void cmos_write (uint8_t offset, uint8_t value) {
  uint8_t tmp = inb (0x70);
  outb (0x70, (tmp & 0x80) | (offset & 0x7F));
  outb (0x71, value);
}

void cmos_dump (uint16_t *dest) {
  uint16_t i = 0;
  for (i; i < 128; ++i) {
    outb (0x70, i);
    dest[i] = inb (0x71);
  }
}
