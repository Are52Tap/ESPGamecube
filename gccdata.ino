#include "gccdata.h"

inline bool validateGCBytes(uint8_t* bytes){
    return (bytes[0] & 0xC0 == 0xC0) && bitRead(bytes[1],1);
}

inline bool validateGCBits(uint8_t* bits, uint8_t length){
    return length == 64 && bits[0] == 0 && bits[1] == 0 && bits[8] == 1;
}

bool GCCData::setFromBits(uint8_t* bits, uint8_t length){
    if(!validateGCBits(bits, length)) return false;
    for(int i = 0; i < 64; i++)
        bitWrite(this->bytes[i/8],7-(i%8),bits[i]);
    return true;
}

bool GCCData::setFromBytes(uint8_t* bytes, uint8_t length){
    if(length != 8 || !validateGCBytes(bytes)) return false;
    memcpy(this->bytes,bytes,64);
    return true;
}

bool GCCData::originSet(){
    return bitRead(bytes[0],5);
}

bool GCCData::start(){
    return bitRead(bytes[0],4);
}

bool GCCData::buttonY(){
    return bitRead(bytes[0],3);
}

bool GCCData::buttonX(){
    return bitRead(bytes[0],2);
}

bool GCCData::buttonB(){
    return bitRead(bytes[0],1);
}

bool GCCData::buttonA(){
    return bitRead(bytes[0],0);
}

bool GCCData::bumperL(){
    return bitRead(bytes[1],6);
}

bool GCCData::bumperR(){
    return bitRead(bytes[1],5);
}

bool GCCData::buttonZ(){
    return bitRead(bytes[1],4);
}

bool GCCData::dPadUp(){
    return bitRead(bytes[1],3);
}

bool GCCData::dPadDown(){
    return bitRead(bytes[1],2);
}

bool GCCData::dPadRight(){
    return bitRead(bytes[1],1);
}

bool GCCData::dPadLeft(){
    return bitRead(bytes[1],0);
}

uint8_t GCCData::joystickX(){
    return bytes[2];
}

uint8_t GCCData::joystickY(){
    return bytes[3];
}

uint8_t GCCData::cStickX(){
    return bytes[4];
}

uint8_t GCCData::cStickY(){
    return bytes[5];
}

uint8_t GCCData::triggerL(){
    return bytes[6];
}

uint8_t GCCData::triggerR(){
    return bytes[7];
}

bool GCCData::validate(){
    return validateGCBytes(this->bytes);
}

void plotTransform(uint8_t t){
    Serial.print(t);
}

void plotBoolTransform(bool t){
    Serial.print(t ? 80 : 0);
}

void GCCData::plot(){
    
    Serial.print("start: ");
    plotBoolTransform(start());
    Serial.print('\t');

    Serial.print("buttonY: ");
    plotBoolTransform(buttonY());
    Serial.print('\t');

    Serial.print("buttonX: ");
    plotBoolTransform(buttonX());
    Serial.print('\t');

    Serial.print("buttonB: ");
    plotBoolTransform(buttonB());
    Serial.print('\t');

    Serial.print("buttonA: ");
    plotBoolTransform(buttonA());
    Serial.print('\t');

    Serial.print("buttonZ: ");
    plotBoolTransform(buttonZ());
    Serial.print('\t');
    
    Serial.print("buttonL: ");
    plotBoolTransform(bumperL());
    Serial.print('\t');

    Serial.print("buttonR: ");
    plotBoolTransform(bumperR());
    Serial.print('\t');

    Serial.print("dPadUp: ");
    plotBoolTransform(dPadUp());
    Serial.print('\t');

    Serial.print("dPadDown: ");
    plotBoolTransform(dPadDown());
    Serial.print('\t');

    Serial.print("dPadLeft: ");
    plotBoolTransform(dPadLeft());
    Serial.print('\t');

    Serial.print("dPadRight: ");
    plotBoolTransform(dPadRight());
    Serial.print('\t');

    Serial.print("joystickX: ");
    plotTransform(joystickX());
    Serial.print('\t');

    Serial.print("joystickY: ");
    plotTransform(joystickY());
    Serial.print('\t');

    Serial.print("cStickX: ");
    plotTransform(cStickX());
    Serial.print('\t');

    Serial.print("cStickY: ");
    plotTransform(cStickY());
    Serial.print('\t');

    Serial.print("triggerL: ");
    plotTransform(triggerL());
    Serial.print('\t');

    Serial.print("triggerR: ");
    plotTransform(triggerR());
    Serial.println();

}

void GCCData::print(){
}