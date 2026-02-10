 /*
  ******************************************************************************
  * @file timecalc.c
	*
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Dieses Modul implementiert elementare Zeitmessungen.
  *        Es greift auf das timer.c Module der ITS Library zu 
  *        und kapselt dieses.	
  *******************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "timecalc.h"
#include "timer.h"

void initTimeCalc(void){
   // initialisiere TIM_2 gemaess der Library des ITS Boards
	initTimer();
}

// This function returns the span of time in usec
double timerDiffToSec(uint32_t ts1, uint32_t ts2) {
   uint32_t v = (ts2 - ts1); // unsigned, no problem with overflow
	return ((double)v)/((double)(TICKS_PER_US*1000*1000));
}

// EOF
