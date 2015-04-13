#ifndef __rtc__
#define __rtc__

#define KERNEL_YEAR 2015

static const uint8_t *MONTH[] = {
  "January",
  "February",
  "March",
  "April",
  "May",
  "Juny",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};

static const uint8_t *DAY[] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

typedef struct date {
  uint16_t d;
  uint16_t dow;
  uint16_t M;
  uint32_t Y;
} date_t;

typedef struct time {
  uint16_t s;
  uint16_t m;
  uint16_t h;
} time_t;

int     init_rtc      (void);
date_t  rtc_get_date  (void);
time_t  rtc_get_time  (void);

#endif
