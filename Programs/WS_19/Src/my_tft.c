
/**
  ******************************************************************************
  * @file    my_tft.c 
  * @author  <I H R  N A M E>
  * @date    22.01.2020
  * @brief   Dieses Modul implementiert eine einfache Textausgabe auf dem TFT 
	*          Display.
  ******************************************************************************
  */
#include "stdio.h"
#include <fonts.h>
#include <HAW_lcd.h>


/**
	******************************************************************************
  * @brief  Diese Funktion loescht die aktuelle Ausgabe auf dem TFT Display und
	*         initialisiert es für die zeilenweise Ausgabe von Text.
  *
  * @retval None
  *****************************************************************************/
void initTFTAndClr(void) {
}

/**
	******************************************************************************
  * @brief  Diese Funktion gibt folgende Textzeilen auf den ersten drei 
  *         Zeilen des TFT Display aus:
	*                Druecken Sie den Taster.
	*                Warten Sie 10 Sekunden.
	*                Druecken Sie den Taster erneut.	
	*         Jede Zeile wird mit einem Zeilenumbruch beendet.
  * @retval None
  *****************************************************************************/
void TFTputWelcomeStr(void) {
}

/**
	******************************************************************************
  * @brief  Diese Funktion gibt eine Zeitspanne gemaess des folgenden printf
	*         Formatstrings aus:
	*                   "Zeitspanne %.1f Sekunden.\n\r"
	*         wobei die Zeitspanne die im Formatstring referenzierte float Variable
	*         ist.
  *         Diese Ausgabe wird immer in Zeile 4 geschrieben. Somit werden alte 
  *         Ausgaben ueberschrieben.
  *
  * @param  time  Die auszugebende Zeitspanne in Sekunden.
	*
  * @retval None
  *****************************************************************************/
void TFTputTestResult(float time) {
}

// EOF
