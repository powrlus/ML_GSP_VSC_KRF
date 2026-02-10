/**
  * @file update.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Dieses Modul berechnet Winkel und Winkelgeschwindigkeit. 
  */
#ifndef _UPDATE_H
#define _UPDATE_H

#include <stdint.h>

/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert den aktuellen Winkel zurück, der im 
 *          vorgegebenen Intervall aktualisiert wird.
 *
 *  @return Aktuelle Winkel [1/10 Grad]
 ****************************************************************************************/
int64_t getAngle(void);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert den aktuellen Winkelgeschwindigkeit zurück, die im 
 *          vorgegebenen Intervall aktualisiert wird.
 *
 *  @return Aktuelle Winkelgeschwindigkeit
 ****************************************************************************************/
double getAngularSpeed(void);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion initialisiert dieses Modul.
 *
 *  @return None
 ****************************************************************************************/
void initUpdate(void);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion überprüft, ob das Update Zeitfenster verstrichen ist und 
 *          aktualisiert dann Winkel und Winkelgeschwindigkeit.
 *
 *  @return None
 ****************************************************************************************/
void updateUpdate(void);

#endif

// EOF
