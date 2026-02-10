/**
  ******************************************************************************
  * @file    my_timer.h 
  * @author  <I H R  N A M E>
  * @date    22.01.2020
  * @brief   Dieses Modul implementiert einfache Funktionen zur Behandlung von
	*          Zeitspannen. Es basiert auf dem Modul timer, das den Timer TIM2 
	*          verwendet. 
  ******************************************************************************
  */

#ifndef _MY_TIMER_H
#define _MY_TIMER_H

#include <stdint.h>

/**
  ******************************************************************************
  * @brief  Diese Funktion initialisiert das Modul.
  *         Insbesondere wird das timer Modul initialisiert.	
  *
  * @retval None
  ******************************************************************************/
extern void initMyTimer(void);

/**
  ******************************************************************************
  * @brief  Diese Funktion liefert den aktuellen Zeitstempel von TIM2 zurueck.
  *
  * @retval Aktueller Time Stamp von TIM2
  *****************************************************************************/
extern uint32_t getTS(void);
	
/**
  ******************************************************************************
  * @brief  Diese Funktion verzoegert die Programmausfuehrung - wartet - fuer 
  *         timeInUs Microsekunden.
  *
  * @param  timeInUs Verzoegerungszeit in us
  *
  * @retval Bei fehlerfreier Ausfuehrung wird eine 0 zurueckgegeben. Ist die
  *         Verzoegerungszeit groesser gleich der Zeitspanne, die das Timerregister
  *         speichern kann, verzoegert die Funktion nicht und liefert -1 zurueck.
  *****************************************************************************/
extern int wait(unsigned int timeInUs);

/**
  ******************************************************************************
  * @brief  Diese Funktion liefert die Zeitspanne zwischen den Zeitstempeln 
  *         ts2 und ts1 in us zurueck.
  *
  * @param  ts1 Zeitstempel des ersten Zeitpunkts.
  *
  * @param  ts2 Zeitstempel des zweiten Zeitpunkts.
  *
  * @retval Zeitspanne zwischen ts1 und ts2 in us.
  *****************************************************************************/
extern uint32_t getTimeSpan(uint32_t ts1, uint32_t ts2);

#endif
// EOF
