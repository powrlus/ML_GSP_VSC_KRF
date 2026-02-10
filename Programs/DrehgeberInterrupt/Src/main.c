/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor f�r technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    2020-08-23
 * @brief   L�sung GSP Drehgeber Polling
 ******************************************************************************
 */
 
 // TODO Teste Ausgabe und Berechnung von Winkeln
 // TODO Problem Ungenauigkeit Winkelgeschwindigkeit bei 20000 Grad / s
 // TODO Zeiten Bestimmen und Test max Speed

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "fsm.h"
#include "input.h"
#include "output.h"
#include "timecalc.h"
#include "update.h"
#include "TFTOutput.h"

#define UPDATE_TFT_INTERVAL     (250*1000)   // minimal interval for TFT upate (in us)

/*
 *    E i n i g e  t y p i s c h e  Z e i t e n
 
 *  - Mit -Ofast dauert ein Durchlauf durch die ISR ca. 400 ns
      Damit k�nnen Winkelgeschwindigkeiten von 450000 Grad / s verarbeitet werden.
			
	  - Bei h�heren Winkelgeschwindigkeiten bliebt keine Zeit f�r das Auslesen eines 
		  konsistenten Satzes von Zeitstempel und Phasenanzahl aus der ISR.
			
 *  - Formeln
 *    0.3�   = 1 tick/Phasewechsel
 *    1�     = 10/3 tick  
 *
 *    Berechnen aus dem Abstand d zwischen zwei Ticks die Winkelgeschwindigkeit v in �/s
 *    
 *      d [s] / 1 [tick] = 1 [s] / y [ticks]    
 *      d [s/tick] = 1/y [s/tick]
 *
 *      y [ticks/s] = 1/d [tick/s]
 * 
 *      v [�/s] = 0.3 [�/tick] /d [ticks/s] = 0.3/d [�/s]   
 *   
 *  - Winkelgeschwindigkeit      Abstand zwischen zwei Phase
 *        0.3/d �/s                       d s
 *        37500 �/s                       8 us
 *          375 �/s                     800 us 
 *            2 �/s                     150 ms
 *            1 �/s                     300 ms
 *          8.8 �/s                      34 ms
 *            8 �/s                    37,5 ms
 *            9 �/s                   33,33 ms
 *           10 �/s                      30 ms
 *
 *  - Daten aus meinem Programm
 *    Ohne Compiler Optimierungen : 
 *        Einsprung in die ISR : 370 ns
 *	 	  Laufzeit der ISR (ohne Ein- und Aussprung) : 1120 ns
 *    Mit Compiler Optimierungen : 
 *        Einsprung in die ISR : 190 ns
 *		  Laufzeit der ISR (ohne Ein- und Aussprung) : 180 ns
 *        Winkelgeschwindigkeit die noch geht 450.000 Grad/s 
 *           Bei einer höheren Geschwindigkeit sind Zeitstempel und Flankenwert nicht mehr 
             konsistent.
 */

int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(500 + DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	if (!checkVersionFlashFonts()) {
	   // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
		Error_Handler();
	}
	initTimeCalc();
   initInput();
   setupTerm(); 
	initFSM(giveCurrentPhase());
   initUpdate();

	int64_t curAngle       = getAngle();  // unit 1/10 Grad
	double curAngularSpeed = getAngularSpeed();
	fillResultBuffer(curAngle, curAngularSpeed);
   
	// super loop based on direct digital control (DDC)
	while(1) {
		// sample RT entities - read input
	   bool errorReset     = errorResetButtonPressed();
		
	   // execution of control algorithm 
		if (errorReset) { // reset - independent of current state
			 resetFSM();
       initUpdate();
		}
		// execute FSM
      updateUpdate();
				
		// calculate new set points for actors (new values for LEDs)			
		uint8_t LEDscounterOutput = (uint8_t) getPhaseCount(NULL); // just output lowest 8 bit, independ of sign etc.
    bool LEDbackwardDirection = backwardRotation();
    bool LEDforwardDirection  = forwardRotation();
    bool LEDerr               = inErrorState();
			
		int64_t newAngle               = getAngle();   // unit 1/10 Grad
		double newAngularSpeed         = getAngularSpeed();
		if ((curAngle != newAngle) || (curAngularSpeed != newAngularSpeed)) {
			curAngle = newAngle;
			curAngularSpeed = newAngularSpeed;
			fillResultBuffer(curAngle, curAngularSpeed);
		}
      // output set points to actors (set LEDs)
      setCounterLEDs(LEDscounterOutput) ;
      setForwardLED(LEDforwardDirection); 
      setBackwardLED(LEDbackwardDirection);
		setErrorLED(LEDerr); 
		printResultBuffer();
	} // End of super loop
   // This point will never be reached
}

// EOF
