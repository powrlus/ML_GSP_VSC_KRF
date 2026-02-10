/**
 *******************************************************************
 * @file    input.h 
 * @author  Franz Korf
 *        	HAW-Hamburg
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @date    WS 2016
 * @brief   Header file of input module 
 *******************************************************************
*/

#ifndef _INPUT_H
#define _INPUT_H
#include <stdbool.h>
#include <stm32f4xx_hal.h>

typedef enum {PhaseA = 0, PhaseB = 2, PhaseC = 3, PhaseD = 1} PhaseType;

/**
 *****************************************************************************************
 *  @brief   Diese Funktion initialisiert die Input Pins und deren Ports.
 *
 *  @return  Ist der Error-Reset-Button gedrueckt, liefert die Funktion true zurueck.
 *           Ansonsten false.
 ****************************************************************************************/
void initInput(void);

/**
 *****************************************************************************************
 *  @brief   Diese Funktion liefert den Status des Error-Reset-Buttons zurueck.
 *
 *  @return  Ist der Error-Reset-Button gedrueckt, liefert die Funktion true zurueck.
 *           Ansonsten false.
 ****************************************************************************************/
bool errorResetButtonPressed(void);

/**
 *****************************************************************************************
 *  @brief   Diese Funktion liefert die aktuellen Werte von Channel A und B zurueck.
 *           Verwende inline function zur Beschleunigung der ISR.
 *
 *  @return  bit 0 == 1 <=> Channel B == high 
 *           bit 1 == 1 <=> Channel A == high
 *           bit 2 ... 7 : stets 0
 ****************************************************************************************/
// Mapping of channel value pairs to phases
// PhaseA = 0x00, /* A = 0 B = 0 */
// PhaseD = 0x01, /* A = 0 B = 1 */
// PhaseB = 0x02, /* A = 1 B = 0 */
// PhaseC = 0x03, /* A = 1 B = 1 */

#define OFFSET_CHANNEL_B       					   0    // channel B connected to BIT 0
#define OFFSET_CHANNEL_A       					   1    // channel A connected to bit 1
#define INPUT_REG_CHANNELS							   GPIOG  // Channels werden über AUX0 und AUX1 angeschlossen
#define CHANNEL_A_AND_B_MASK						   ((0x01 << OFFSET_CHANNEL_A) | (0x01 << OFFSET_CHANNEL_B))

static inline PhaseType giveCurrentPhase(void){
   return (PhaseType)(INPUT_REG_CHANNELS->IDR & CHANNEL_A_AND_B_MASK);
}

#endif
// EOF
