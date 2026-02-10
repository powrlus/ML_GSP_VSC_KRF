/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 ******************************************************************************
 */

#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "timecalc.h"
#include "myerr.h"
#include "TFTOutput.h"
#include "scanBus.h"
#include "tempsensor.h"

#define TIME_BETWEEN_MEASUREMENTS (1000 * 1000)
/*
 * @brief This functions reads  PDROM of a device connected to
 *        the 1-wire bus.
 *        Pre Requirement: Only one device is connected to the bus.
 */
void readOnePdrom(void) {
	PDROM p = readRomId();
 	printROM(p);
	sleepUs(TIME_BETWEEN_MEASUREMENTS);
}

void oneTempSensorConnected(void) {
   PDROM p = readRomId();
	double temp = readTemp(false, p);
	printROMandTemp(p, temp);
	sleepUs(TIME_BETWEEN_MEASUREMENTS);
}

void oneTempSensorConnectedWithoutReadingRomId(void) {
   PDROM p = 0;
	double temp = readTemp(true, p);
	printROMandTemp(p, temp);
	sleepUs(TIME_BETWEEN_MEASUREMENTS);
}

void multipleTempSensorConnected(void) {
   if (!scanPDROMS()) {
      printError();
      resetError();
   } else {
      printHeadline(); 
      for(int i = 0; i < giveNumberOfPDROMS(); i++) {
         PDROM p = givePDROM(i);
         double temp = readTemp(false, p);
         printROMandTemp(p, temp);
      }
   }
   sleepUs(TIME_BETWEEN_MEASUREMENTS);
}

int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	if (!checkVersionFlashFonts()) {
      // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
		Error_Handler();
	}
	initTimeCalc();
	oneWireBusInit();
	resetError();
   setupTerm(); 
	
   while (1) {
      // readOnePdrom();
      // oneTempSensorConnectedWithoutReadingRomId();
      // oneTempSensorConnected();
	   multipleTempSensorConnected();
      printError();
      resetError();
   }	
}

// EOF
