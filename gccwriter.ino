#include "Arduino.h"
#include "gccwriter.h"
#include "timingcycles.h"

void GCCWriter::async_write(uint8_t pin){
    uint32_t time;
    asm volatile ("rsr %0, ccount" : "=r"(time));
    uint64_t diff;
    if(time <= lastTime){
        diff = (0x00000000FFFFFFFF-(uint64_t)lastTime)+time;
    } else {
        diff = (uint64_t)time-(uint64_t)lastTime;
    }

    
    if(diff > US1-8 && diff < US1+12){
    } else if(diff > US3-16 && diff < US3+24){
    } else {
    }
    
    noInterrupts();
    pinMode(pin, OUTPUT);

    if(segment){
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }

    pinMode(pin, INPUT_PULLUP);
    interrupts();
}


ICACHE_RAM_ATTR uint32_t GCCWriter::sync_write(uint8_t* bits, uint8_t length, uint8_t pin){
    
    //noInterrupts(); // caller responsibe for specifying no interrupts.
    uint8_t mask = _BV(pin);
    pinMode(pin, OUTPUT);
    GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, mask);
    //digitalWrite(pin, HIGH);
    delayMicroseconds(3);

    uint8_t seg = 0;
    uint32_t startTime = 0;
    uint32_t period = 0;
    uint32_t c = _getCycleCount();
    uint8_t pos = 0;

/**
 * Types:
 *  0 - uninit
 *  1 - low for 1us
 *  2 - low for 3us
 *  3 - high for 1us
 *  4 - high for 3us
 */
    //Serial.println("Going!");
    while(pos < length){
        while(getTimeDifference(startTime, (c = _getCycleCount())) < period);
        //Serial.println(c);
        startTime = c;
        if(seg == bits[pos]) period = (US3);
        else period = US1;
        //period=(period*49)/40;
        if(seg){
            GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, mask);
            //digitalWrite(pin, HIGH);
            seg = 0;
            pos++;
        } else {
            GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, mask);
            //digitalWrite(pin, LOW);
            seg = 1;
        }
    }
    //delayMicroseconds(5);
            //delayMicroseconds(500);
    
    //GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, mask);

    //pinMode(pin, INPUT_PULLUP);
    //interrupts(); // see above note

    return _getCycleCount();
}