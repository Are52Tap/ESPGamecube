#pragma once

#include "Arduino.h"


class GCCData{
    private:
        uint8_t bytes[8];
        GCCData(uint8_t* bytes, uint8_t length);
    public:
        GCCData(){};
        bool setFromBits(uint8_t* bits, uint8_t length);
        bool setFromBytes(uint8_t* bytes, uint8_t length);
        bool originSet();
        bool start();
        bool buttonY();
        bool buttonX();
        bool buttonB();
        bool buttonA();
        bool bumperL();
        bool bumperR();
        bool buttonZ();
        bool dPadUp();
        bool dPadDown();
        bool dPadRight();
        bool dPadLeft();
        uint8_t joystickX();
        uint8_t joystickY();
        uint8_t cStickX();
        uint8_t cStickY();
        uint8_t triggerL();
        uint8_t triggerR();
        bool validate();
        void print();
        void plot();
        

};


