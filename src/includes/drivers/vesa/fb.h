#ifndef __fb__
#define __fb__

#include <system/typedef.h>

typedef struct fbinfo {
  uint32_t   resx;
  uint32_t   resy;
  uint16_t   pitch;
  uint8_t    fb_length;
  int8_t    *fb;
} fbinfo_t;

int init_vesa (void);

#endif
