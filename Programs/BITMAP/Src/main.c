/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 *
 *					25.04.2022 Tobias De Gasperis: printf hinzugefuegt
 ******************************************************************************
 */
 
 
 // TODO Compiler Flag  -DUSE_FULL_LL_DRIVER entfernen
 // TODO LL Dateien entfernen
 //
 // Zeitmessungen
 //     Standardfall 2:35 Minuten
 

#include "main.h"

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "BMP_types.h"
#include "input.h"
#include "colorTable.h"
#include "headers.h"
#include "errorhandler.h"
#include "lineHandling.h"
#include "LCDbufferedOutput.h"
#include "stdint.h"
#include "uncompressedBMP.h"
#include "compressedBMP.h"
#include "perfTimer.h"


#define  MAX_BOX_WIDTH   MAX_SCALE
#define  MAX_BOX_HEIGHT  MAX_SCALE


static int handlePicture(void){
   GUI_clear(BLACK);
   initPrintBuf();
   openNextFile();
   BITMAPINFOHEADER ih;
   
   RAISE_NOK(readHeaders());
	RAISE_NOK(getInfoHeader(&ih));
   initLineHandling(ih.biWidth, ih.biHeight);
   RAISE_NOK(readColorTable());
   RETURN_NOK_ON_ERR((ih.biWidth > MAX_PIC_WIDTH) || (ih.biHeight > MAX_PIC_HEIGHT), "main: picture to large.");
   if (BI_RGB == ih.biCompression) {
      // umcompressed
      RAISE_NOK(printUncompressedBitMap());
   } else if (BI_RLE8  == ih.biCompression) {
      // 8 Bit compressed
      RAISE_NOK(printCompressedBipMap(ih.biWidth)); 
   } else {
      ERR_HANDLER(true, "main: unexpected file format.");
      return NOK;
   }
   RETURN_NOK_ON_ERR(EOF != nextChar(), "EOF expected.");
   return EOK;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	if (!checkVersionFlashFonts()) {
	    // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
		Error_Handler();
	}
	
	initInput();
	initPerfTimers();
	
	while (1){
      if (EOK == handlePicture()){
         delay(3000);
      } else {
         delay(15000);
      }
   }	
}

// EOF
