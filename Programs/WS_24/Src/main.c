/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    22. Jan. 2025
 * @brief   Die Klausuraufgabe Kniffel.
 *
 ******************************************************************************
 */

#include "main.h"
#include <stdlib.h>
#include "init.h"
#include "io.h"
#include "display.h"
#include "kniffel.h"
#include "test.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"


int main(void){
   // Initialisierung der HW
   initITSboard();
	 GUI_init(DEFAULT_BRIGHTNESS);
	
#ifdef AUFGABE3
   testIO();
#endif

#ifdef AUFGABE4
   testDisplay();
#endif

#ifdef AUFGABE5 
	 testKniffel();
#endif
	
   
}
// EOF