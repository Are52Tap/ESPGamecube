#include "Arduino.h"
#include "gccman.h"
#include "esp8266_peri.h"
//#include "core_esp8266_wiring_digital.cpp"

#ifndef ICACHE_RAM_ATTR
#error("bad")
#endif

ICACHE_RAM_ATTR int gc_read(uint8_t pin, uint8_t* bytes, uint8_t length){
	int i = /*__*/digitalRead(pin);
	return i;
}

/*ICACHE_RAM_ATTR void gc_read7(){
	//Serial.println("Triggered!");
	uint8_t pin = GameCubeManager::list[0]->getPin();
	int i = gc_read(pin);
	GameCubeManager::list[0]->setRead(i);
}*/

ICACHE_RAM_ATTR inline int gc_read(uint8_t pin){
	//int i = /*__*/digitalRead(pin);
	/*Serial.println();
	Serial.println(((GPI & (1 << ((pin) & 0xF))) != 0));
	Serial.println(GPI & (1 << ((pin) & 0xF)));
	Serial.println(1 << ((pin) & 0xF));
	Serial.println(1 << ((pin) & 0xF),BIN);
	Serial.println(GPI);
	Serial.println(GPI,BIN);
	Serial.println(((GPI & (1 << ((pin) & 0xF))) != 0));
	Serial.println();*/
	return GPIP(pin);
}