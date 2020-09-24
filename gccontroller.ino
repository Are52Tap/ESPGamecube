#include "gccontroller.h"
#include "gcman.h"
#include "gamecube_comm.h"
#include "gccreader.h"
#include "gccwriter.h"
#include "timingcycles.h"

GameCubeController::GameCubeController(const uint8_t _pin) : pin(_pin){
    this->gccreader = new GCCReader();
    this->gccwriter = new GCCWriter();
    //GameCubeManager::registerController(this);
}


GameCubeController::GameCubeController(const uint8_t _pin, bool _sync) : GameCubeController(_pin){
    begin(_sync);
}

bool GameCubeController::begin(bool _sync){
    noInterrupts();
    init();
    gccreader->sync_read(this->pin,lastIOc);
    origin();
    gccreader->sync_read(this->pin,lastIOc);
    interrupts();
    if(_sync){
        sync = 1;
        return true;
    }
#if 0
    else{
        noInterrupts();
        sync = 0;
        pinMode(this->pin,INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(this->pin), GameCubeManager::handlers[this->pin], CHANGE);
        interrupts();
    }
#endif
    return true;
}

uint8_t GameCubeController::getPin(){
    return this->pin;
}

void GameCubeController::setRumble(bool rumble){
    pollBits[23] = rumble ? 1 : 0;
}

bool GameCubeController::getRumble(){
    return pollBits[23];
}

ICACHE_RAM_ATTR void GameCubeController::poll(){
    //gccreader->cleanup();
    lastIOc = this->gccwriter->sync_write(this->pollBits, 25, this->pin);
}

ICACHE_RAM_ATTR void GameCubeController::init(){
    uint8_t initBits[9] = {0,0,0,0, 0,0,0,0, 1};
    lastIOc = this->gccwriter->sync_write(initBits, 9, this->pin);
}

ICACHE_RAM_ATTR void GameCubeController::origin(){
    uint8_t originBits[9] = {0,1,0,0, 0,0,0,1, 1};
    lastIOc = this->gccwriter->sync_write(originBits, 9, this->pin);
}

ICACHE_RAM_ATTR void GameCubeController::read(){
    //noInterrupts();
    gccreader->sync_read(this->pin, lastIOc);
    //gccreader->printContent();
    //gccreader->printTypeBuffer();
    //gccreader->printTimings();
    //interrupts();
}

ICACHE_RAM_ATTR void GameCubeController::setRead(int val){
    //return this->gccreader->interrupt_sync_read(val);
}

bool GameCubeController::getData(GCCData* data){
    if(this->gccreader->getSize() != 64) return false;
    uint8_t bits[64];
    this->gccreader->getBits(bits,64);
    return data->setFromBits(bits,64);
}

void GameCubeController::tick(){
    gccreader->cleanup();
    noInterrupts();
    poll();
    read();
    //process();
    interrupts();
    process();
}

void GameCubeController::process(){
    this->gccdata = GCCData();
    if(!getData(&gccdata)){
        //Serial.println("NO GOD NO. NOOOO");
    }
}

GCCData GameCubeController::getDataCopy(){
    return (this->gccdata);
}

GCCData& GameCubeController::getData(){
    return (this->gccdata);
}
