#include "Arduino.h"
#include "gccontroller.h"
#include "timingcycles.h"

GameCubeController gccs(D2);


void setup(){
    Serial.begin(115200);
    gccs.begin(true);
    //pinMode(D6,OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D6, INPUT_PULLUP  );
    // delay(2);
    // yield();
    // gccs.getReader().printTypeBuffer();
    gccs.setRumble(false);
    //gccs.poll();
    //gccs.read();
    // delay(2);
    // yield();
    // gccs.getReader().printTypeBuffer();
    
    /*while(true){
        digitalWrite(D2, HIGH);
        delayMicroseconds(200);
        digitalWrite(D2, LOW);
        delayMicroseconds(200);
        digitalWrite(D2, HIGH);
        delayMicroseconds(500);
        digitalWrite(D2, LOW);
        delayMicroseconds(500);
    }*/
}

int lastSize = 0;
int lastTypeSize = 0;
int lastTimingsSize = 0;

void loop(){
    /*if(gccs.getReader().size > lastSize){
        gccs.getReader().printContent();
        lastSize = gccs.getReader().size;
    }
    // if(gccs.getReader().typeBuffSize > lastTypeSize){
        //gccs.getReader().printTypeBuffer();
    //     lastTypeSize = gccs.getReader().typeBuffSize;
    // }
    if(gccs.getReader().timesSize > lastTimingsSize){
        gccs.getReader().printTimings();
        lastTimingsSize = gccs.getReader().timesSize;
    }*/
        //delay(1000);
        //gccs.handshake();
        gccs.tick();
        //gccs.getReader().printContent();
        gccs.getData().plot();
        gccs.setRumble(digitalRead(D6) == LOW);
        //Serial.print(digitalRead(D6) == LOW);
        delay(10);
        //uint8_t spec[4] = {0,1,1,1};
        //gccs.getWriter().sync_write(spec,4,gccs.getPin());
        //yield();
        //gccs.getReader().printTypeBuffer();
        // if(gccs.read(){

        // }
        //(analogRead(0)+analogRead(0))%2;
        //digitalWrite(D6, (analogRead(0)+analogRead(0))%2 ? HIGH : LOW);

}