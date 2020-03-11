#pragma once

#include "Arduino.h"


ICACHE_RAM_ATTR int gc_read(uint8_t pin, uint8_t* bytes, uint8_t length);

ICACHE_RAM_ATTR inline int gc_read(uint8_t pin);