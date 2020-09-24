#pragma once

#include "gamecube_comm.h"
#include "gccontroller.h"

//#define GCPinHandler(pin) pinHandler#pin()

namespace GameCubeManager{
    GameCubeController* controllers[4] = {nullptr};
    GameCubeController* byPin[21] = {nullptr};

    ICACHE_RAM_ATTR inline void pinHandler(uint8_t pin){
        byPin[pin]->getReader().interrupt_sync_read(pin);
        //Serial.print(i);
        //Serial.print(":");
        //Serial.println();
    }
    
    ICACHE_RAM_ATTR void pinHandler0(){return pinHandler(0);}
    ICACHE_RAM_ATTR void pinHandler1(){return pinHandler(1);}
    ICACHE_RAM_ATTR void pinHandler2(){return pinHandler(2);}
    ICACHE_RAM_ATTR void pinHandler3(){return pinHandler(3);}
    ICACHE_RAM_ATTR void pinHandler4(){return pinHandler(4);}
    ICACHE_RAM_ATTR void pinHandler5(){return pinHandler(5);}
    ICACHE_RAM_ATTR void pinHandler6(){return pinHandler(6);}
    ICACHE_RAM_ATTR void pinHandler7(){return pinHandler(7);}
    ICACHE_RAM_ATTR void pinHandler8(){return pinHandler(8);}
    ICACHE_RAM_ATTR void pinHandler9(){return pinHandler(9);}
    ICACHE_RAM_ATTR void pinHandler10(){return pinHandler(10);}
    ICACHE_RAM_ATTR void pinHandler11(){return pinHandler(11);}
    ICACHE_RAM_ATTR void pinHandler12(){return pinHandler(12);}
    ICACHE_RAM_ATTR void pinHandler13(){return pinHandler(13);}
    ICACHE_RAM_ATTR void pinHandler14(){return pinHandler(14);}
    ICACHE_RAM_ATTR void pinHandler15(){return pinHandler(15);}
    ICACHE_RAM_ATTR void pinHandler16(){return pinHandler(16);}
    ICACHE_RAM_ATTR void pinHandler17(){return pinHandler(17);}
    ICACHE_RAM_ATTR void pinHandler18(){return pinHandler(18);}
    ICACHE_RAM_ATTR void pinHandler19(){return pinHandler(19);}

    void (*handlers[20])(void) = {
        pinHandler0,pinHandler1,pinHandler2,pinHandler3,pinHandler4,
        pinHandler5,pinHandler6,pinHandler7,pinHandler8,pinHandler9,
        pinHandler10,pinHandler11,pinHandler12,pinHandler13,pinHandler14,
        pinHandler15,pinHandler16,pinHandler17,pinHandler18,pinHandler19
    };

    int size = 0;

    void registerController(GameCubeController* ptr){
        controllers[size++] = ptr;
        byPin[ptr->getPin()] = ptr;
    }

    /*ICACHE_RAM_ATTR void pinHandler(){
        list[0]->setRead(gc_read(list[0]->getPin()));
        //Serial.print(i);
        //Serial.print(":");
        //Serial.println();
    }*/
};