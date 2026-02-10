/*
  ******************************************************************************
  * @file    	tempsensor.h
  * @author  	Franz Korf
  *        	    HAW-Hamburg
  *          	Labor fuer technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    2016-04-29
  * @brief   This module implements the interface to temperature sensor
******************************************************************************  */

#ifndef _TEMPSENSOR_H
#define _TEMPSENSOR_H

#include <stdbool.h>
#include "oneWireBus.h"

#define FAMILY_CODE_DS18S20        0x10
#define FAMILY_CODE_DS18B20        0x28

#define WRONG_TEMPERATURE_VALUE     200

/**
 * @brief This functions return the contents of product  data ROM
 *        Requirement: Only one sensor is connected to one wire bus.
 *
 * @retval product data ROM
 */

PDROM readRomId(void);

double readTemp(bool skipROMCommand, PDROM rom);

#endif // _TEMPSENSOR_H
// EOF
