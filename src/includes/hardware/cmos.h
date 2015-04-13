#ifndef __cmos__
#define __cmos__

#include <system/typedef.h>

uint8_t cmos_read   (uint8_t);
void    cmos_write  (uint8_t, uint8_t);
void    cmos_dump   (uint16_t *);

#endif
