/**
  * @file fsm.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header of finite state machine module. 
  *        Die FSM verwaltet Phasewechsel, Drehrichtung und den Phasenzähler.     
  */
#ifndef _FSM_H
#define _FSM_H

#include <stdbool.h>
#include <stdint.h>
#include "input.h"

/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert die aktuaelle Anzahl der Phasenwechsel und 
 *          Beachtung der Drehrichtung.
 *
 *  @return Aktuelle Winkel in 1/10 
 ****************************************************************************************/
int64_t getPhaseCount(uint32_t *ts);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion initialisiert die FSM.
 *
 *  @param  phase Die akuelle Phase, die von Kanal A und B gebildet wird.
 *
 *  @return none
 ****************************************************************************************/
void initFSM(PhaseType phase);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die FSM zurück (Fehlerzustand und Phasenzähler).
 *
 *  @return none
 ****************************************************************************************/
void resetFSM(void);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert den Fehlerstatus der FSM.
 *
 *  @return true <=> Mindestens ein Phasenwechsel wurde nicht erkannt.
 ****************************************************************************************/
bool inErrorState(void);

/**
 *****************************************************************************************
 *  @brief  Bei einer Vorwärtsdrehung liefert diese Funktion true zurück.
 *
 *  @return true <=> Der Drehgeber dreht sich vorwärts.
 ****************************************************************************************/
bool forwardRotation(void);

/**
 *****************************************************************************************
 *  @brief  Bei einer Rückwärtsdrehung liefert diese Funktion true zurück.
 *
 *  @return true <=> Der Drehgeber dreht sich rückwärts.
 ****************************************************************************************/
bool backwardRotation(void);

#endif

// EOF
