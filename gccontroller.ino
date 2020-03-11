#include "gccontroller.h"
#include "gccman.h"
#include "gamecube_comm.h"
#include "gccreader.h"
#include "gccwriter.h"

GameCubeController::GameCubeController(const uint8_t _pin) : pin(_pin){
    this->gccreader = new GCCReader();
    this->gccwriter = new GCCWriter();
    GameCubeManager::registerController(this);
}


GameCubeController::GameCubeController(const uint8_t _pin, bool _sync) : GameCubeController(_pin){
    begin(_sync);
}

bool GameCubeController::begin(bool _sync){
    init();
    gccreader->sync_read(this->pin);
    origin();
    gccreader->sync_read(this->pin);
    noInterrupts();
    if(_sync){
        sync = 1;
        return true;
    } else{
        interrupts();
        sync = 0;
        pinMode(this->pin,INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(this->pin), GameCubeManager::handlers[this->pin], CHANGE);
        interrupts();
    }
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

void GameCubeController::poll(){
    //Serial.println("3");
    return this->gccwriter->sync_write(this->pollBits, 25, this->pin);
    //Serial.println("4");
}

void GameCubeController::init(){
    //Serial.println("3");
    uint8_t bits[9] = {0,0,0,0, 0,0,0,0, 1};

    return this->gccwriter->sync_write(bits, 9, this->pin);
    //Serial.println("4");
}

void GameCubeController::origin(){
    //Serial.println("3");
    uint8_t bits[9] = {0,1,0,0, 0,0,0,1, 1};

    return this->gccwriter->sync_write(bits, 9, this->pin);
    //Serial.println("4");
}

void GameCubeController::read(){
    noInterrupts();
    gccreader->sync_read(this->pin);
    gccreader->printContent();
    interrupts();
}

ICACHE_RAM_ATTR void GameCubeController::setRead(int val){
    //return this->gccreader->interrupt_sync_read(val);
}