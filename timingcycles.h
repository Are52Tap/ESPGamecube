#pragma once
#define NS250 20
#if F_CPU == 160000000
#define NS250 40
#elif F_CPU == 80000000
#error 80Mhz is not supported on this library at this point in time.
#define NS250 20
#else
#error Bad news everyone! This is not esp8266
#endif
#define NS500 (2 * NS250)
#define US1 (2 * NS500)
#define US2 (2 * US1)
#define US3 (3 * US1)
#define MS1 (1000 * US1)
#define MS50 (50 * MS1)
//(+25% error)*(4us/byte)*(64bytes)=320us
#define GCCResponseTime25P (320 * US1)

#include "Arduino.h"

static uint32_t _getCycleCount(void) __attribute__((always_inline));
static inline uint32_t _getCycleCount(void) {
  uint32_t ccount;
  __asm__ __volatile__("rsr %0,ccount":"=a" (ccount));
  return ccount;
}

static inline uint32_t getTimeDifference(uint32_t then, uint32_t now){
    if(now <= then){
      return (0xFFFFFFFF-then)+now;
    }
    return now-then;
}
