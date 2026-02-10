/**
  * @file timecalc.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file of timecalc Module. 
  */

#ifndef _TIMECALC_H
#define _TIMECALC_H
#include <stdint.h>
#include <timer.h>

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
static inline uint32_t currentTimeStamp(void) { return getTimeStamp(); }

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
 double timerDiffToSec(uint32_t ts1, uint32_t ts2);

#endif // _ZEITMESSUNG_H
// EOF
