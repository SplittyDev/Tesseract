#include <system/typedef.h>
#include <io/terminal.h>
#include <io/ports.h>
#include <io/memory.h>

uint8_t x;
uint8_t y;
uint8_t foreground;
uint8_t background;
uintptr_t *ptr;

void putc_internal (uint8_t, bool_t);
void checkoverflow (void);
uint16_t makecolor (void);
uint16_t makeattrib (uint8_t);
size_t where (void);

void init_terminal (void) {
  x = 0;
  y = 0;
  foreground = COLOR_WHITE;
  background = COLOR_BLACK;
  ptr = (uintptr_t *)TEXTMEMPTR;
}

void putc_internal (const uint8_t chr, bool_t singleop) {
  switch (chr) {
    case KEY_BACKSPACE:
    if (x > 0)
      x--;
    break;
    case KEY_TAB:
    x = (x + 8) & ~(8 - 1);
    break;
    case KEY_CARRIAGE_RETURN:
    x = 0;
    break;
    case KEY_NEWLINE:
    x = 0;
    y++;
    break;
    default:
    ptr[where ()] = makeattrib (chr);
    x++;
    break;
  }

  checkoverflow ();
  scroll ();

  if (singleop)
    cursor ();
}

void putc (const uint8_t chr) {
  putc_internal (chr, true);
}

void puts (const uint8_t *str) {
  size_t i = 0;
  while (str[i] != KEY_TERMINATE)
    putc_internal (str[i++], false);
  cursor ();
}

void scroll (void) {
  if (y >= TERMINAL_HEIGHT) {
    uint8_t tmp  = y - TERMINAL_HEIGHT + 1;
    uint8_t tmp2 = (TERMINAL_HEIGHT - tmp) * TERMINAL_WIDTH;
    memcopy (ptr, ptr + tmp * TERMINAL_WIDTH, tmp2 * 2);
    memset (ptr + tmp2, makeattrib (KEY_BLANK), TERMINAL_WIDTH);
    y = TERMINAL_HEIGHT - 1;
  }
}

void clear (void) {
  size_t i = 0;
  for (; i < TERMINAL_HEIGHT; i++)
    memset (ptr + i * TERMINAL_WIDTH, KEY_BLANK, TERMINAL_WIDTH);
  x = 0;
  y = 0;
  cursor ();
}

void cursor (void) {
  outb (0x3D4, 14);
  outb (0x3D5, where () >> 8);
  outb (0x3D4, 15);
  outb (0x3D5, where ());
}

void checkoverflow (void) {
  if (x > TERMINAL_WIDTH) {
    x = 0;
    y++;
  }
}

size_t where (void) {
  return y * TERMINAL_WIDTH + x;
}

uint16_t makecolor (void) {
  return foreground | (background << 4);
}

uint16_t makeattrib (uint8_t chr) {
  return chr | (makecolor () << 8);
}
