/* Copyright (C) 2014 - GruntTheDivine (Sloan Crandell)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
    char c = *(format + i);
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
        case 'i':
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

char *sprintf (char buf[], const char *format, ...) {
  va_list argp;
  va_start (argp, format);
  vsprintf (buf, format, argp);
  va_end (argp);
  return buf;
}

void printf (const char *format, ...) {
  va_list argp;
  va_start (argp, format);
  char buf[512];
  memset ((void *)buf, 0, 512);
  vsprintf (buf, format, argp);
  va_end (argp);
  puts (buf);
}
