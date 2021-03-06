#pragma once

#include "Arduino.h"
#include "gccreader.h"
#include "gccwriter.h"
#include "gccdata.h"

class GameCubeController{
    private:
        const uint8_t pin;
        //volatile* int read = 5;
        uint8_t pollBits[25] = {0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,1, 0,0,0,0, 0,0,0,0, 1};
        uint8_t sync = -1; // -1=>unset, 0=>async, 1=>sync
        GCCReader* gccreader;
        GCCWriter* gccwriter;
        GCCData gccdata;
        //static ICACHE_RAM_ATTR void pinHandler();
        ICACHE_RAM_ATTR void poll();
        ICACHE_RAM_ATTR void init();
        ICACHE_RAM_ATTR void origin();
        ICACHE_RAM_ATTR void read();
    public:
        volatile uint32_t lastIOc;
        GameCubeController(const uint8_t pin);
        GameCubeController(const uint8_t pin, bool sync);
        bool begin(bool sync);
        ICACHE_RAM_ATTR void setRead(int i);
        inline GCCReader& getReader(){return *gccreader;}
        inline GCCWriter& getWriter(){return *gccwriter;}
        bool getData(GCCData* data);
        GCCData& getData();
        GCCData getDataCopy();
        uint8_t getPin();
        void tick();
        void process();
        void setRumble(bool yeah);
        bool getRumble();

};
