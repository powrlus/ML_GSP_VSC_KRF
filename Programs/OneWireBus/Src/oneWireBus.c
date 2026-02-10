 /*
  ******************************************************************************
  * @file    	oneWireBus.c
  * @author  	Franz Korf
  *        	    HAW-Hamburg
  *          	Labor fuer technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    2016-04-29
  * @brief   This module implements basic access functions for oneWireBus
	*
	* Fix 
    Simulation und TI Board verwenden unterschiedliche Prozessoren, deren 
	  GPIOs unterschiedlich angesteuert werden. Das gilt insbesondere fuer
 	  die Programmierung der PullUp Widerstände.
	  Damit der selbe Code fuer beide Varianten laeuft, wird der ONE_WIRE_BUS_PIN
	  nur noch im Output Mode betrieben (alter Version: Verwende Input Mode und
    PullUp).
	  Dabei wird ONE_WIRE_BUS_PIN mit Standard Fall auf 1 gesetzt, so dass der interne
	  Widerstand des OpenDrain Mode eine 1 treibt. 
	 
  ******************************************************************************  */

/* Includes ------------------------------------------------------------------*/
#include "oneWireBus.h"
#include "timecalc.h"
#include "myerr.h"
#include "hal.h"
#include "crc.h"

// Interface to one wire bus
#define BUSPORT         		       GPIOD
#define MESS_PIN				           7
#define PARASITIC_POWER_SUPPLY_PIN    1
#define ONE_WIRE_BUS_PIN              0

uint8_t getFamilyCode(uint64_t pdrom){
	 return (uint8_t) (pdrom & 0xFF);
}

 void oneWireBusInit(void) {
	 // set output mode for open drain pin and drive 1
	 setOpenDrainMode(BUSPORT, ONE_WIRE_BUS_PIN);
	 setOutputMode(BUSPORT, ONE_WIRE_BUS_PIN);
	 writePin(BUSPORT, ONE_WIRE_BUS_PIN, 1); 

	 // set output mode for push pull port
	 // Push Pull Mode driving 1 via external resistor all the time
	 setPushPullMode(BUSPORT, PARASITIC_POWER_SUPPLY_PIN);
	 setOutputMode(BUSPORT, PARASITIC_POWER_SUPPLY_PIN);
	 writePin(BUSPORT, PARASITIC_POWER_SUPPLY_PIN, 1);

	 // set pin von time measurement
	 setOpenDrainMode(BUSPORT, MESS_PIN);
	 setOutputMode(BUSPORT, MESS_PIN);
}

void writeBit(unsigned char val){
	 // drive bus with 0 for 60 / 6 us for writing 0 / 1
	 writePin(BUSPORT, ONE_WIRE_BUS_PIN, 0);
	 sleepUs((0 == val) ? 60 : 6);
   // set bus to 1 for 10 / 64 us for writing 0 / 1
	 writePin(BUSPORT, ONE_WIRE_BUS_PIN, 1);
	 sleepUs((0 == val) ? 10 : 64);
}

void writeByte(unsigned char val){ 
	 for (int i = 0; i < 8; i++){
		 writeBit(val & 0x01);
		 val = val >> 1;
	 }
}

void writeByteSeq(unsigned char * buf, unsigned int size){
	// buf[0] : LSB .... buf[size-1] : MSB
	for (int i = 0; i < size; i++) { 
		 writeByte(*(buf + i)); 
	}
}

unsigned char readBit(void){
   unsigned char v;
	 // set bus to low for 6 us
	 writePin(BUSPORT, ONE_WIRE_BUS_PIN, 0);
	 sleepUs(6);	
   // chanage to input mode and wait for 9 us	
	 writePin(BUSPORT, ONE_WIRE_BUS_PIN, 1);
	 sleepUs(9);	
	 // read input and wait for 55 us
	 v = (readPin(BUSPORT, ONE_WIRE_BUS_PIN)) ? 1 : 0;
    sleepUs(55);	
	 return v;
}

unsigned char readByte(void){
   int i = 0;
   unsigned char v = 0;
   for (i = 0; i < 8; i++) { 
      v = v | (readBit() << i); 
   }
   return v;
}

bool readByteSeq(unsigned char * buf, unsigned int size){
	// little endian buf[0] : LSB .... buf[size-1] : MSB
	for (int i = 0; i < size; i++) { 
	   *(buf + i) = readByte(); 
	}
	return checkCRC(size, buf);
}

bool resetBus(void){
   // set bus to low for 480 us
	writePin(BUSPORT, ONE_WIRE_BUS_PIN, 0);
   sleepUs(480); 
	writePin(BUSPORT, ONE_WIRE_BUS_PIN, 1);
	// For next 480 us: check of at least one slave 
	// that acknowledge the reset by driving bus with 0

   uint32_t startTime = currentTimeStamp();

	bool ackOfSlaves = false;
   while((((double)480) / 1000000) >= timerDiffToSec(startTime, currentTimeStamp())){
      ackOfSlaves = ackOfSlaves || !readPin(BUSPORT, ONE_WIRE_BUS_PIN);
   }
	return ackOfSlaves;
}

void energizeBus(const uint32_t t){
	writePin(BUSPORT, ONE_WIRE_BUS_PIN, 1); // Zur Sicherheit, damit bei einem Programmierfehler kein Kurzschluss entsteht.
	setPushPullMode(BUSPORT, ONE_WIRE_BUS_PIN);
	sleepUs(t);
	setOpenDrainMode(BUSPORT, ONE_WIRE_BUS_PIN);
}

static PDROM byteSeqToPDROM(const unsigned char size, unsigned char buf[size]){
	 PDROM rom = 0x00;
	 for (int i = 0; i < size; i++) { 
		 rom = rom  | (((PDROM)(buf[i])) << (8*i));
	 }
	 return rom;
}

static void PDROMToByteSeq(PDROM rom, const unsigned char size, unsigned char buf[size]){
	 for (int i = 0; i < size; i++) {
     buf[i] = (unsigned char)(rom >> (8*i));
	 }
}
	 
PDROM readRomData(void){
	unsigned char buf[PDROM_SIZE]; 
	if (ERR_HANDLER(!readByteSeq(buf, PDROM_SIZE), CRC_ERR)) {
		 return 0x00;
	}
	return byteSeqToPDROM(PDROM_SIZE, buf);
}

PDROM giveTestRomData(void){
   // Using the example of the 1-wire bus crc document (an27.pdf) this functions tests 
   // function checkCRCPDROM works
	unsigned char buf[PDROM_SIZE] = {0x02, 0x1C, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xA2}; 
	if (ERR_HANDLER(!checkCRC(PDROM_SIZE, buf), CRC_ERR)){
		 return 0x00;
	}	
	return  byteSeqToPDROM(PDROM_SIZE, buf);
}

void writeRomData(PDROM rom){
	unsigned char buf[PDROM_SIZE]; 
	PDROMToByteSeq(rom, PDROM_SIZE, buf);
	writeByteSeq(buf, sizeof(buf)/sizeof(buf[0]));
}

// EOF
