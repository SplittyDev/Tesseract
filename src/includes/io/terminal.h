#ifndef __terminal__
#define __terminal__
#include <system/typedef.h>

#define TEXTMEMPTR          0xB8000

#define TERMINAL_WIDTH      80
#define TERMINAL_HEIGHT     25

#define BRIGHT              0x8
#define COLOR_BLACK         0x0
#define COLOR_BLUE          0x1
#define COLOR_GREEN         0x2
#define COLOR_CYAN          0x3
#define COLOR_RED           0x4
#define COLOR_MAGENTA       0x5
#define COLOR_BROWN         0x6
#define COLOR_LIGHT_GRAY    0x7
#define COLOR_DARK_GRAY     0x0 + BRIGHT
#define COLOR_LIGHT_BLUE    0x1 + BRIGHT
#define COLOR_LIGHT_GREEN   0x2 + BRIGHT
#define COLOR_LIGHT_CYAN    0x3 + BRIGHT
#define COLOR_LIGHT_RED     0x4 + BRIGHT
#define COLOR_LIGHT_MAGENTA 0x5 + BRIGHT
#define COLOR_YELLOW        0x6 + BRIGHT
#define COLOR_WHITE         0x7 + BRIGHT

#define KEY_BACKSPACE       '\b'
#define KEY_TAB             '\t'
#define KEY_CARRIAGE_RETURN '\r'
#define KEY_NEWLINE         '\n'
#define KEY_TERMINATE       '\0'
#define KEY_BLANK           ' '

void init_terminal (void);
void putc (const uint8_t);
void puts (const uint8_t *);
void scroll (void);
void cursor (void);
void clear (void);

#endif
