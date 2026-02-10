/**
  * @file TFTOoutput.c
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief This modules implements a simple output to TFT monitor.
	*        It defines one TFT terminal areas. 
	*
  */

#include "TFTOutput.h"
#include <stdio.h>
#include "oneWireBus.h"
#include "tempsensor.h"
#include "terminal.h"
#include "LCD_GUI.h"
#include "fontsFLASH.h"


// Definition of terminal area
#define TERM_FONT          2
#define TERM_POS_X_TEXT    2
#define TERM_POS_Y         1
#define TERM_COLUMNS_TEXT 44
#define TERM_LINES        12

#define OUT_STR_SIZE  128
static char outStr[OUT_STR_SIZE];	

static Terminal term = INVALID_TERM;

void setupTerm(void){
   // For speeding up TFT display use separate window for left and right-most column.
   // These column contain text that does not change. Hence they will be printed once at 
   // startup phase. This function is not implemented in the current software.
   Coordinate topLeft = {0,0}; 
   Coordinate bottomRight = {LCD_WIDTH-1,LCD_HEIGHT-1};
   term = genTerm(topLeft, bottomRight, BLUE, YELLOW, &Font16FLASH);
	clearTerm(&term);
}

void showError(char * file, int line, int errno){
   // TFT_cls();
	setTextColorTerm(RED, &term);	
	snprintf(outStr, OUT_STR_SIZE - 1 , "\n%s line %d: ERROR: %d\n", file, line, errno);
	printTerm(outStr, &term);
}

void printROM(PDROM rom) {
   clearTerm(&term);	 
	setTextColorTerm(YELLOW, &term);	
	snprintf(outStr, OUT_STR_SIZE - 1 , "ROM ID = 0x%016llx\n", rom);
	printTerm(outStr, &term);
}

void printROMandTemp(PDROM rom, double temp) {
	uint8_t family = getFamilyCode(rom);
	setTextColorTerm(YELLOW, &term);	
	if ((FAMILY_CODE_DS18S20 == family) || (FAMILY_CODE_DS18B20 == family)){
      printTerm("DS18",&term);
		setTextColorTerm(RED, &term);	
		printTerm((FAMILY_CODE_DS18S20 == family)?"S":"B", &term); 
		setTextColorTerm(YELLOW, &term);	
		printTerm("20 ", &term);
   } else {
      printTerm("unknown\n",&term);
	}
	snprintf(outStr, OUT_STR_SIZE - 1 , "0x%16llx ", rom);
	printTerm(outStr,&term);
	if (WRONG_TEMPERATURE_VALUE != temp) {
      snprintf(outStr, OUT_STR_SIZE - 1 , "%lf\n", temp);
	} else {
		setTextColorTerm(RED,&term);
		snprintf(outStr, OUT_STR_SIZE - 1 , "ERROR\n");		 
   }
	printTerm(outStr,&term);
	setTextColorTerm(YELLOW, &term);
}

void printHeadline(void) {
   clearTerm(&term);	 
	setTextColorTerm(YELLOW, &term);	
	printTerm("Sensor  PDROM              Temp. [C]\n", &term);	
}

void printStr(char *buf) {
   setTextColorTerm(YELLOW, &term);	
	printTerm(buf, &term);	
}
// EOF
