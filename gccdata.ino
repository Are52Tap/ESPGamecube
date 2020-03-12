#include "gccdata.h"

inline bool validateGCBytes(uint8_t* bytes){
    return (bytes[0] & 0xC0 == 0xC0) && bitSet(bytes[1],1);
}

inline bool validateGCBits(uint8_t* bits, uint8_t length){
    return length == 64 && bits[0] == 0 && bits[1] == 0 && bits[8] == 1;
}

bool GCCData::setFromBits(uint8_t* bits, uint8_t length){
    if(!validateGCBits(bits, length)) return false;
    for(int i = 0; i < 64; i++)
        bitWrite(this->bytes[i/8],i%8,bits[i]);
    return true;
}

bool GCCData::setFromBytes(uint8_t* bytes, uint8_t length){
    if(length != 8 || !validateGCBytes(bytes)) return false;
    memcpy(this->bytes,bytes,64);
    return true;
}

bool GCCData::originSet(){
    return bitSet(bytes[0],2);
}

bool GCCData::start(){
    return bitSet(bytes[0],3);
}

bool GCCData::buttonY(){
    return bitSet(bytes[0],4);
}

bool GCCData::buttonX(){
    return bitSet(bytes[0],5);
}

bool GCCData::buttonB(){
    return bitSet(bytes[0],6);
}

bool GCCData::buttonA(){
    return bitSet(bytes[0],7);
}

bool GCCData::bumperL(){
    return bitSet(bytes[1],1);
}

bool GCCData::bumperR(){
    return bitSet(bytes[1],2);
}

bool GCCData::buttonZ(){
    return bitSet(bytes[1],3);
}

bool GCCData::dPadUp(){
    return bitSet(bytes[1],4);
}

bool GCCData::dPadDown(){
    return bitSet(bytes[1],5);
}

bool GCCData::dPadRight(){
    return bitSet(bytes[1],6);
}

bool GCCData::dPadLeft(){
    return bitSet(bytes[1],7);
}

int8_t GCCData::joystickX(){
    return bytes[2];
}

int8_t GCCData::joystickY(){
    return bytes[3];
}

int8_t GCCData::cStickX(){
    return bytes[4];
}

int8_t GCCData::cStickY(){
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

void plotTransform(int8_t t){
    Serial.print(t);
}

void plotTransform(bool t){
    Serial.print(t ? "32" : "0");
}

void GCCData::plot(){
    /*Serial.print("originSet: ");
    plotTransform(originSet());
    Serial.print('\t');

    Serial.print("buttonY: ");
    plotTransform(buttonY());
    Serial.print('\t');

    Serial.print("buttonX: ");
    plotTransform(buttonX());
    Serial.print('\t');*/

    Serial.print("buttonB: ");
    plotTransform(buttonB());
    Serial.print('\t');

    Serial.print("buttonA: ");
    plotTransform(buttonA());
    Serial.print('\t');

    /*Serial.print("buttonZ: ");
    plotTransform(buttonZ());
    Serial.print('\t');
    
    Serial.print("buttonL: ");
    plotTransform(bumperL());
    Serial.print('\t');

    Serial.print("buttonR: ");
    plotTransform(bumperR());
    Serial.print('\t');

    Serial.print("dPadUp: ");
    plotTransform(dPadUp());
    Serial.print('\t');

    Serial.print("dPadDown: ");
    plotTransform(dPadDown());
    Serial.print('\t');

    Serial.print("dPadLeft: ");
    plotTransform(dPadLeft());
    Serial.print('\t');

    Serial.print("dPadRight: ");
    plotTransform(dPadRight());
    Serial.print('\t');*/

    Serial.print("joystickX: ");
    plotTransform(joystickX());
    Serial.print('\t');

    Serial.print("joystickY: ");
    plotTransform(joystickY());
    Serial.print('\t');

    /*Serial.print("cStickX: ");
    plotTransform(cStickX());
    Serial.print('\t');

    Serial.print("cStickY: ");
    plotTransform(cStickY());
    Serial.print('\t');

    Serial.print("triggerL: ");
    plotTransform(triggerL());
    Serial.print('\t');

    Serial.print("triggerR: ");
    plotTransform(triggerR());*/
    Serial.println();

}

void GCCData::print(){
}