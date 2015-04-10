#include <stdlib/stdlib.h>
#include <stdlib/stdio.h>
#include <stdlib/stdarg.h>
#include <io/memory.h>
#include <io/terminal.h>

void vsprintf (char *dest, const char *format, va_list argp) {
  int len = strlen (format);
  int ptr = 0;
  int i = 0;
  char nbuf[16];
  for (; i < len; i++) {
    char *c = format[i];
    if (c == '%') {
      char spec = format[++i];
      switch (spec) {
        case '%':
        dest[ptr++] = '%';
        break;
        case 's':
        strcpy ((char *)(dest + ptr), va_arg (argp, char *));
        ptr = strlen (dest);
        break;
        case 'd':
        itoa (nbuf, va_arg (argp, int));
        strcpy ((char *)(dest + ptr), nbuf);
        dest += strlen (nbuf);
        break;
        case 'x':
        itox (nbuf, va_arg (argp, int));
        strcpy ((char *)(dest + ptr), nbuf);
        dest += strlen (nbuf);
        break;
        case 'p':
        memset (nbuf, 0, 16);
        memset (nbuf, '0', 8);
        itox (nbuf, va_arg (argp, int));
        strcpy ((char *)(dest + ptr), nbuf);
        nbuf[8] = 0;
        dest += 8;
        break;
        case 'c':
        dest[ptr++] = va_arg (argp, int);
        break;
      }
    } else {
      dest[ptr++] = c;
    }
  }
}

void sprintf (char *dest, const char *format, ...) {
  va_list argp;
  va_start (argp, format);
  vsprintf (dest, format, argp);
  va_end (argp);
}

void printf (char *dest, const char *format, ...) {
  va_list argp;
  va_start (argp, format);
  vsprintf (dest, format, argp);
  va_end (argp);
  puts (dest);
}
