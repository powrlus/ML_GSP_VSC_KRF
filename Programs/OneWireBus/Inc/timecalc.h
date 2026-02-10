/**
  * @file timecalc.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file of timecalc Module. 
  */

#ifndef _TIMECALC_H
#define _TIMECALC_H
#include <stdint.h>

/**
 *****************************************************************************************
 *  @brief  Diese Funktion initialisiert das Modul timecalc.
 *
 *  @return none
 ****************************************************************************************/
void initTimeCalc(void);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert den aktullen Zeitstempel - den Wert des counter Registers
 *          von TIM2 - zurueck.
 *
 *  @return Aktueller Zeitstempel
 ****************************************************************************************/
uint32_t currentTimeStamp(void);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion berechnet die Zeitspanne zwischen zwei Zeitstempeln in Sekunden.
 *          Die Zeitspanne muss kleiner als floor((2^32 - 1) / 90) us = 47,721858 s sein.
 *
 *  @param  ts1 aelterer Zeitstempel 
 *  @param  ts2 neuerer Zeitstempel 
 *
 *  @return Die Zeitspanne zwischen den beiden Zeitstempeln in Sekunden.
 ****************************************************************************************/
 double timerDiffToSec(const uint32_t ts1, const uint32_t ts2);
 
 /**
 * @brief This function implements a sleep function via active waiting
 *
 * @param t Time to sleep (unit us). Range of input value 0 .. (UINT32_MAX-1)/TIM2_CLOCK
 *
 * @return In case of an error the global timing variable will be set.
 */
extern void sleepUs(const uint32_t t);

#endif // _TIMECALC_H
// EOF
