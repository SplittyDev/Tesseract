#ifndef __stdio__
#define __stdio__

#include <stdlib/stdarg.h>

void vsprintf (char *, const char *, va_list);
char *sprintf (char[], const char *, ...);
void printf (const char *, ...);

#endif
