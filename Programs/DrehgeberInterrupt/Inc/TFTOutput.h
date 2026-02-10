/**
  * @file TFToutput.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file of TFT output module. 
  */

#ifndef _TFTOUTPUT_H
#define _TFTOUTPUT_H

#include "fsm.h"
	
/*
 ****************************************************************************************
 *  @brief   This function initialize an output termimal of TFT display
 *
 *  @return  void 
 ****************************************************************************************/
void setupTerm(void);

/*
 ****************************************************************************************
 *  @brief  The TFToutput module uses two output buffers. One for the angle to be output 
 *          and one for angular speed to be output.
 *          This function fills both buffers with new values.
 *
 *  @param  angle New angle - unit 1/10 degee
 *	 @param  angularSpeed New angular speed - unit 1/10 degee
 *
 *  @return void 
 ****************************************************************************************/
void fillResultBuffer(int64_t angle, double angularSpeed);

/*
 ****************************************************************************************
 *  @brief  After result buffers has been updated, this function prints them to TFT display. 
 *          Depending on a module internal parameter the output is done character by 
 *          character - one character per function call - or all at once. 
 *
 *  @return     void 
 ****************************************************************************************/
void printResultBuffer(void);

#endif /* _TFTOUTPUT_H */
// EOF
