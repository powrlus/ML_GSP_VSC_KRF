/**
  ******************************************************************************
  * @file    io.h 
  * @author  <I H R  N A M E>
  * @date    22.01.2020
  * @brief   Dieses Modul implementiert GPIO basiertes IO. 
  ******************************************************************************
  */

#ifndef _IO_H
#define _IO_H

#include <stdbool.h>
#include <stdint.h>

#define BUTTON_NOT_PRESSED		0
#define BUTTON_PRESSED				1
#define BUTTON_ERR					 -1

/**
	******************************************************************************
  * @brief  Diese Funktion initialisiet die verwendeten Ports.
	* 
  * @retval None
  *****************************************************************************/
extern void initIO(void);

/**
	******************************************************************************
  * @brief  Diese Funktion setzt die Error LED.
	*
  * @param  on Ist der Parameter true, wird die Error LED angeschaltet. Ansonsten
	*         wird sie ausgeschaltet.
	* 
  * @retval None
  *****************************************************************************/
extern void setErrLED(bool on);

/**
	******************************************************************************
  * @brief  Diese Funktion setzt die Status LED.
	*
  * @param  on Ist der Parameter true, wird die Status LED angeschaltet. Ansonsten
	*         wird sie ausgeschaltet.
	* 
  * @retval None
  *****************************************************************************/
extern void setStatusLED(bool on);

/**
	******************************************************************************
  * @brief  Diese Funktion fragt den Taster ab. Er wird softwaremaessig
	*         entprellt.
	* 
  * @retval  BUTTON_NOT_PRESSED : Der Taster ist nicht gedrueckt.
  *          BUTTON_PRESSED     : Der Taster ist gedrueckt.
  *          BUTTON_ERR         : Fehlerfall	
  *****************************************************************************/
extern int8_t buttonPressed(void);

#endif
// EOF
