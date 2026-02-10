/*
  ******************************************************************************
  * @file    	tempsensor.c
  * @author  	Franz Korf
  *        	    HAW-Hamburg
  *          	Labor fuer technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    2016-04-29
  * @brief   This module implements the interface to temperature sensor
******************************************************************************  */

/* Includes ------------------------------------------------------------------*/
#include "tempsensor.h"
#include <stdio.h>
#include "terminal.h"
#include "timecalc.h"
#include "myerr.h"
#include "oneWireBus.h"
#include "TFTOutput.h"

PDROM readRomId(void){
   // This function requires that only one sensor is connected to the bus.
	if (ERR_HANDLER(!resetBus(), RESET_ERR)){
      return 0x00;
	}
	writeByte(READ_ROM_CMD);
	return readRomData();
}

static bool selectSensor(bool skipROMCommand, PDROM rom) {
   if (ERR_HANDLER(!resetBus(), RESET_ERR)){
      return false; 
	 } 
	 if (skipROMCommand) {
       writeByte(SKIP_ROM_CMD);
	 } else {
		 writeByte(MATCH_ROM_CMD);
		 writeRomData(rom);
	 }
	 return true;
}

static double convertTempRegToCelsius(int16_t reg) {
   // convert to float and devide by 16
	return ((float) reg) / 16;
}

double readTemp(bool skipROMCommand, PDROM rom) {
   // select sensor 
	if (! selectSensor(skipROMCommand, rom)) {
      return WRONG_TEMPERATURE_VALUE; 
	}	 
	// send convert temperature command
	writeByte(CONVERT_T_CMD);
	// switch to push pull for converting temperature
	energizeBus(750000);
	// select sensor 
	if (! selectSensor(skipROMCommand, rom)) {
      return WRONG_TEMPERATURE_VALUE; 
	}
	// read data from scratchpad and check CRC
	unsigned char scratchPad[SCRATCHPADSIZE];
	for (int i = 0; i < SCRATCHPADSIZE; i++) { scratchPad[i] = 0x00; }
	writeByte(READ_SCP_CMD);
	if (!readByteSeq(scratchPad, SCRATCHPADSIZE)) {
      return WRONG_TEMPERATURE_VALUE; 		 
	}	 
	int16_t tempReg = (scratchPad[1] << 8);
	tempReg = tempReg | scratchPad[0];
	// calculate temperature in celsius
	// Convert DS18S20 Temperature to TS18B20 Temperature
	if (FAMILY_CODE_DS18S20 == getFamilyCode(rom)) {
      tempReg = (tempReg << 3);		 
	}		 
	double temp = convertTempRegToCelsius(tempReg);
   if ((temp < -55) || (temp > 125)) {
      // Temperatur ausserhalb des Bereichs
		return WRONG_TEMPERATURE_VALUE; 		 
	}
	return temp;
}

/*
 * Test functions
 */
void testConvertTempRegToCelsius(void) {
	const int bufSize = 512;
	char buf[bufSize];	
	double   res[] = {125   , 85    , 25.0625, 10.125, 0.5   , 0     , -0.5  , -10.125, -25.0625, -55   };     
	uint16_t reg[] = {0x07D0, 0x0550, 0x0191 , 0x00A2, 0x0008, 0x0000, 0xFFF8, 0xFF5E , 0xFE6F  , 0xFC90}; 

  for (int i = 0; i < (sizeof(res) / sizeof(double)); i++) {
     snprintf(buf, sizeof(buf) - 1 , "exp  val. : %lf\n", res[i]);
	  printStr(buf);
     snprintf(buf, sizeof(buf) - 1 , "calc val. : %lf\n", convertTempRegToCelsius(reg[i]));
     printStr(buf);
     sleepUs(2000000);
     sleepUs(2000000);
  }	
}

// EOF
