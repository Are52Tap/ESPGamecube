#include "Arduino.h"
#include "gccreader.h"
#include "timingcycles.h"
#include "gamecube_comm.h"

/**
 * Types:
 *  0 - uninit
 *  1 - low for 1us
 *  2 - low for 3us
 *  3 - high for 1us
 *  4 - high for 3us
    always: // shouldn't happen
        (1,2) - imp
        (2,1) - imp
        (3,4) - imp
        (4,3) - imp
    pos%2 == 1: // ending on low impossible
        (1,3) - imp due to ending & (1+1)!%4
        (1,4) - valid
        (2,3) - valid
        (2,4) - (3+3)!%4
        (3,1) - imp
        (4,1) - imp
        (3,2) - imp
        (4,2) - imp
    pos%2 == 0: // ending on low imp & starting on high imp
        (1,3) - (1+1)!%4
        (1,4) - imp
        (2,3) - imp
        (2,4) - imp due to starting & (3+3)!%4
        (3,1) - imp
        (4,1) - imp
        (3,2) - imp
        (4,2) - imp
 */

ICACHE_RAM_ATTR bool GCCReader::sub_update(uint8_t read, uint32_t time){
    /*uint64_t diff;
    if(time <= lastTime){
        diff = (0x00000000FFFFFFFF-(uint64_t)lastTime)+time;
    } else {
        diff = (uint64_t)time-(uint64_t)lastTime;
    }*/
    uint32_t diff = getTimeDifference(lastTime,time);

    /*int64_t diff = ((int64_t)((uint64_t)time))-((int64_t)((uint64_t)lastTime));
    if(diff < 0)
        diff+=0x00000000FFFFFFFF;*/
    //uint8_t type = this->lastType;
    //if(diff < US1/2) return; // something wrong
    if(diff > NS250 && diff <= US2+NS250){
        if(read){
            // from Low for 1us - first segment done
            this->lastType=1;
            if(typeBuffSize < 256){typeBuff[typeBuffSize++] = this->lastType;}
        } else{
            // from High for 1us - second segment done
            if(this->lastType == 2){
                //buffer[size/8] = (buffer[size/8] & (~(1 << (size%8)))) | (0 << size%8);
                buffer[size++] = 0;
                //size++;
            }
            this->lastType=3;
            if(typeBuffSize < 256){typeBuff[typeBuffSize++] = this->lastType;}
        }
    } else if(diff > US2+NS250 && diff < 2*US3){
        if(read){
            // from Low for 3us - first segment done
            this->lastType=2;
            if(typeBuffSize < 256){typeBuff[typeBuffSize++] = this->lastType;}
        } else{
            // from High for 3us - second segment done, OR from init
            if(this->lastType == 1){
                //buffer[size/8] = (buffer[size/8] & (~(1 << (size%8)))) | (1 << (size%8));
                buffer[size++] = 1;
                //size++;
            }
            this->lastType=4;
            if(typeBuffSize < 256){typeBuff[typeBuffSize++] = this->lastType;}
        }
    } else if(this->lastType != -1){
        if(diff > 10000){
            #ifdef GC_READER_DEBUG
            Serial.println("OOF");
            Serial.println(lastTime);
            Serial.println(time);
            Serial.println(diff);
            #endif
            return false;
            ESP.reset();
        } else {
            #ifdef GC_READER_DEBUG
            Serial.println("OOF2");
            Serial.println((float)diff/(float)US1);
            #endif
            return false;
            //Serial.println(diff);
        }
        //Serial.print("timeyOld =");
        //Serial.print(lastTime);
        //Serial.print(", timeyNew =");
        //Serial.println(time);
    } else {
        //Serial.println("OOF3");
        //Serial.println((float)diff/(float)US1);
        return true;
        //Serial.println("OOF3");
        //Serial.println(lastTime);
        //Serial.println(time);
        //Serial.println(diff);
    }
    if(changesSize < 256){
        //Serial.println("yo");
        changes[changesSize++] = read;
        times[timesSize++] = diff;
    }
    return true;
}


ICACHE_RAM_ATTR void GCCReader::update(uint8_t read){
    if(this->lastRead == read) return;
    uint32_t time = _getCycleCount();
    sub_update(read,time);
    this->lastRead = read;
    this->lastTime = time;
}


// must take less <1ms or instability will occur
// for reading it should take at worst (+25% error)*(4us/byte)*(64bytes)=320us
ICACHE_RAM_ATTR void GCCReader::interrupt_sync_read(uint8_t pin){
    noInterrupts();
    uint8_t read = gc_read(pin);
    if(read == lastRead) return;
    // TODO fix cleanup();
    uint32_t c = _getCycleCount();
    sub_update(read,c);
        lastRead = read;
        lastTime = c;

    sub_sync_read(pin);
    interrupts();
}

ICACHE_RAM_ATTR uint8_t GCCReader::sync_read(uint8_t pin, uint32_t lastIOc){
    

    //uint32_t startTime = _getCycleCount();//
    uint32_t c;
    uint8_t read;
    uint32_t nextIOc = _getCycleCount();;
    if((read = gc_read(pin)) == lastRead){
        c = _getCycleCount();
        /*uint32_t mustExitBy = c+(MS1/2);
        bool needToPass0 = false;
        if(mustExitBy < c)
            needToPass0 = true;*/
        uint32_t startTime = c;
        while((read = gc_read(pin)) == lastRead){
            //delay(0);
            c = _getCycleCount();
            //if(needToPass0 && c < startTime) needToPass0 = false;
            if(getTimeDifference(startTime,c) > MS50){
                // Serial.print(c);
                // Serial.print(">");
                // Serial.println(mustExitBy);
                #ifdef GC_READER_DEBUG
                Serial.print("start read expired...");
                Serial.println(getTimeDifference(lastIOc,nextIOc));
                #endif
                return 0;
                //goto exit; //return;// 
            }/* else if(getTimeDifference(lastTime,c) > US1*6){
                Serial.println("Special exit: ");
                if(!read)
                    Serial.println("Odd event... Should not exit here!");
                //Serial.println((float)getTimeDifference(lastTime,c)/(double)US1);
                return 0;
            }*/
        }
    }
    c = _getCycleCount();
    /*uint32_t*/ nextIOc = c;//
    sub_update(read,c);
    lastRead = read;
    lastTime = c;

    // do the rest
    sub_sync_read(pin);

    #ifdef GC_READER_DEBUG
    Serial.println(getTimeDifference(lastIOc,nextIOc));
    #endif
    return size;
}

ICACHE_RAM_ATTR void GCCReader::sub_sync_read(uint8_t pin){


    uint32_t startTime = lastTime;
    /*if(!firstBitHandled){
        startTime = _getCycleCount();
    }*/
    //uint32_t mustExitBy = startTime+(GCCResponseTime25P);
    uint8_t read;
    uint32_t c;
    //uint8_t rSize = 64*3; // or 65?
    // Serial.print("begin read:");
    // Serial.print(startTime);
    // Serial.print(',');
    // Serial.println(mustExitBy);
    /*bool needToPass0 = false;
    if(mustExitBy < startTime)
        needToPass0 = true;*/
    uint8_t passes = 0;
    while(size < 64*3){
        //Serial.println('a');
        //Serial.println(mustExitBy);
        //Serial.println();
        while((read = gc_read(pin)) == lastRead){
            c = _getCycleCount();
            //if(needToPass0 && c < startTime) needToPass0 = false;
            if(getTimeDifference(startTime,c) > GCCResponseTime25P){
                // Serial.print(c);
                // Serial.print(">");
                // Serial.println(mustExitBy);
                #ifdef GC_READER_DEBUG
                    Serial.print("read expired after...");
                    Serial.println((float)getTimeDifference(lastTime,c)/(double)US1);
                #endif
                
                return;
                //goto exit; //return;// 
            } else if(getTimeDifference(lastTime,c) > US1*12){

                #ifdef GC_READER_DEBUG
                Serial.println("Special exit: ");
                if(!read)
                    Serial.println("Should not exit here!");
                Serial.println(lastTime);
                Serial.println(c);
                Serial.println((float)getTimeDifference(lastTime,c)/(double)US1);
                Serial.println();
                #endif
                return;
            }
        }
        c = _getCycleCount();
        if(!sub_update(read,c)){
            return;
        }
        lastRead = read;
        lastTime = c;
        //passes++;
    }
    //exit:
    // Serial.print("Completed sync_read with : ");
    // Serial.print(size);
    // Serial.print(", ");
    // Serial.println(passes);
}

void GCCReader::printContent(){
    Serial.print("buff:");
    Serial.print(size);
    Serial.print('\t');
    for(int i = 0; i < size; i++){
        Serial.print(buffer[i]);
        if(i%8==7) Serial.print(' ');
        //Serial.print(' ');
    }
    Serial.println();
    /*for(int i = 0; i < size; i++){
        Serial.print(" ");
    }
    Serial.println("^");*/
}

void GCCReader::printTypeBuffer(){
    Serial.println("types:");
    Serial.println();
    for(int i = 0; i < typeBuffSize; i++){
        Serial.print(typeBuff[i]);
    }
    Serial.println();
}

void GCCReader::printTimings(){
    noInterrupts();
    Serial.println("timings start:");
    Serial.println();
    for(int i = 0; i < changesSize; i++){
        Serial.print(changes[i]);
        Serial.print(":");
        //Serial.print(times[i]);
        //Serial.print("cyc,\t");
        Serial.print((float)times[i]/(float)US1);
        Serial.print("uS");
        Serial.println();
    }
    interrupts();
    Serial.println(":end timings");
}

void GCCReader::cleanup(){
    lastType = -1; 
    changesSize = 0;
    typeBuffSize = 0;
    timesSize = 0;
    size = 0;
}