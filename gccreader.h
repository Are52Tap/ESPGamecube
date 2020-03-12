#pragma once


class GCCReader{
    public:
        volatile uint8_t lastRead = -1;
        volatile uint8_t buffer[256] = {}; // only goes up to 64
        volatile uint8_t size = 0; // where the next byte goes; and current size;
        volatile uint8_t lastRead = -1;
        volatile uint8_t buffer[256] = {}; // only goes up to 16
        volatile uint8_t size = 0; // where the next byte goes; and current size;

        volatile int8_t typeBuff[256] = {};
        volatile uint8_t typeBuffSize = 0;
        
        volatile uint32_t changes[256] = {};
        volatile uint8_t changesSize = 0;
        
        volatile uint32_t times[256] = {};
        volatile uint8_t timesSize = 0;

        volatile uint32_t lastTime = 0;
        volatile int8_t lastType = -1; // -1 = init, 0 = low, 1 = high
        bool sub_update(uint8_t read, uint32_t time);
        void update(uint8_t read);
        uint8_t sync_read(uint8_t pin, uint32_t lastIOc);
        void sub_sync_read(uint8_t pin);
        void interrupt_sync_read(uint8_t pin);
        void printContent();
        void printTypeBuffer();
        void printTimings();
        void cleanup();
        inline uint8_t getSize(){return size;}
        inline uint8_t* getBits(){return buffer;}
};