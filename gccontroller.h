#pragma once

#include "Arduino.h"
#include "gccreader.h"
#include "gccwriter.h"

class GameCubeController{
    private:
        const uint8_t pin;
        //volatile* int read = 5;
        uint8_t pollBits[25] = {0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,1, 0,0,0,0, 0,0,1,0, 1};
        uint8_t sync = -1; // -1=>unset, 0=>async, 1=>sync
        GCCReader* gccreader;
        GCCWriter* gccwriter;
        //static ICACHE_RAM_ATTR void pinHandler();
    public:
        GameCubeController(const uint8_t pin);
        GameCubeController(const uint8_t pin, bool sync);
        bool begin(bool sync);
        void setRead(int i);
        inline GCCReader& getReader(){return *gccreader;}
        inline GCCWriter& getWriter(){return *gccwriter;}
        uint8_t getPin();
        void poll();
        void init();
        void origin();
        void read();
        void setRumble(bool yeah);
        bool getRumble();

};
