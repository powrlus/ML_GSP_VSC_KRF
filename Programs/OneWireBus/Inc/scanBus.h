/*
  ******************************************************************************
  * @file    	scanBus.h
  * @author  	Franz Korf
  *        	    HAW-Hamburg
  *          	Labor fuer technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    2016-11-20
  * @brief   This module scane one wire bus for sensors connected to it
******************************************************************************  */

#ifndef _SCANBUS_H
#define _SCANBUS_H

#include "oneWireBus.h"

unsigned char giveNumberOfPDROMS(void);

PDROM givePDROM(unsigned char n);

bool scanPDROMS(void);

#endif
// EOF
