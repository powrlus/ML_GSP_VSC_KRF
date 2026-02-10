/**
  * @file TFToutput.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file of TFT output module. 
  */

#ifndef _TFTOUTPUT_H
#define _TFTOUTPUT_H

#include "oneWireBus.h"

/*
 ****************************************************************************************
 *  @brief      This function initialize an output termimal of TFT display
 *
 *  @return     void 
 ****************************************************************************************/
void setupTerm(void);

/*
 ****************************************************************************************
 *  @brief      This function prints an error message
 *
 *  @return     void 
 ****************************************************************************************/
void showError(char * file, int line, int errno);

/*
 ****************************************************************************************
 *  @brief      This function prints an ROM image
 *
 *  @return     void 
 ****************************************************************************************/
void printROM(PDROM rom);

void printROMandTemp(PDROM rom, double temp);

void printHeadline(void);

void printStr(char *buf);

#endif /* _TFTOUTPUT_H */
// EOF
