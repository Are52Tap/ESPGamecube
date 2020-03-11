#pragma once

extern "C" {
#include "user_interface.h"
}

class GCCWriter{
    public:
        os_timer_t sendTimer;
        volatile uint32_t lastTime = 0;
        //uint8_t bits[9] = {0,0,1,0, 0,0,0,0, 1};
        //uint8_t bits[9] = {1,1,1,0,1};
        //uint8_t size = 25;
        volatile uint8_t segment = 0;
        void async_write(uint8_t pin);
        void sync_write(uint8_t* bits, uint8_t length, uint8_t pin);


};