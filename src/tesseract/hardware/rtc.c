#include <system/typedef.h>
#include <hardware/rtc.h>
#include <hardware/cmos.h>
#include <io/ports.h>

enum {
  rtc_reg_second      = 0x00,
  rtc_reg_minute      = 0x02,
  rtc_reg_hour        = 0x04,
  rtc_reg_dayofweek   = 0x06,
  rtc_reg_dayofmonth  = 0x07,
  rtc_reg_month       = 0x08,
  rtc_reg_year        = 0x09,
  rtc_reg_century     = 0x00, // 0x32
};

int bcdtoi (uint32_t n, const uint8_t *data) {
  uint32_t result = 0;
  uint32_t i = 0;
  for (; i < n; i++) {
    result *= 100;
    result += (data[i] >> 4) * 10;
    result += data[i] & 0x0F;
  }
  return result;
}

#define bcdtoib(x)  ((x / 16) * 10 + (x & 0xF))

int init_rtc (void) {
  cmos_write (0x0B, cmos_read (0x0B) | 0x40); // IRQ 8
  cmos_write (0x0A, (cmos_read (0x0A) & 0xF0) | 0x0F); // 500ms
}

uint8_t readregb (uint16_t dump[128], uint8_t pos) {
  uint8_t tmp;
  tmp = bcdtoib (dump[pos]);
  return tmp;
}

uint16_t readregs (uint16_t dump[128], uint8_t pos) {
  uint16_t tmp;
  tmp = bcdtoib (dump[pos]);
  return tmp;
}

uint32_t rtc_get_full_year (uint16_t dump[128]) {
  uint32_t Y = readregs (dump, rtc_reg_year);
  Y += (KERNEL_YEAR / 100) * 100;
  if (Y < KERNEL_YEAR)
    Y += 100;
  return Y;
}

date_t rtc_get_date (void) {
  uint16_t dump[128];
  cmos_dump (dump);
  date_t rtcdate = {
    readregs (dump, rtc_reg_dayofmonth),
    readregs (dump, rtc_reg_dayofweek),
    readregs (dump, rtc_reg_month),
    rtc_get_full_year (dump)
  };
  return rtcdate;
}

time_t rtc_get_time (void) {
  uint16_t dump[128];
  cmos_dump (dump);
  time_t rtctime = {
    readregs (dump, rtc_reg_second),
    readregs (dump, rtc_reg_minute),
    readregs (dump, rtc_reg_hour)
  };
  return rtctime;
}
