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
	initTimer(); // initialisiere TIM_2 gemaess der Library des ITS Boards
}

uint32_t currentTimeStamp(void) {
   return getTimeStamp();
}

double timerDiffToSec(const uint32_t ts1, const uint32_t ts2) {
   uint32_t v = (ts2 - ts1); // unsigned, no problem with overflow
   return ((double)v)/((double)(TICKS_PER_US*1000*1000));
}

void sleepUs(const uint32_t t) {
	uint32_t t1 = currentTimeStamp();
	int64_t delayInTicks = (int64_t) t * TICKS_PER_US;

	while (delayInTicks > 0){
	   uint32_t t2 = currentTimeStamp();
	   uint32_t ticksPassed = t2 - t1;
	   delayInTicks = delayInTicks - ticksPassed;
		t1 = t2;
	}
}
// EOF
