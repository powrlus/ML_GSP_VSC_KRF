/**
  * @file upate.c
  * @author Franz Korf, HAW Hamburg 
  * @date October 2016
  * @brief Implementation of finite state machine module. 
  */
  
#include "update.h"
#include "fsm.h"
#include "timecalc.h"
#include "output.h"
#include <stm32f4xx_hal.h>

// for testing
#define DD_SIZE 30
struct {
   int64_t pc;
   uint32_t minTs;
   uint32_t maxTs;
   uint32_t delta;
} dddiff[DD_SIZE];

static void update_dddiff(int64_t pc, uint32_t ts){
   static int nextfreeEntry = 0;
   for(int i = 0; i < nextfreeEntry; i++){
      if (dddiff[i].pc == pc){
         dddiff[i].minTs = (ts < dddiff[i].minTs) ? ts : dddiff[i].minTs;
         dddiff[i].maxTs = (ts > dddiff[i].maxTs) ? ts : dddiff[i].maxTs;
         dddiff[i].delta = dddiff[i].maxTs - dddiff[i].minTs;
         return;
      }
   }
   // new Entry required
   if (nextfreeEntry < DD_SIZE) {
      dddiff[nextfreeEntry].pc = pc;
      dddiff[nextfreeEntry].minTs = ts;
      dddiff[nextfreeEntry].maxTs = ts;   
      dddiff[nextfreeEntry++].delta = 0;   
   }
}

static int64_t angle = 0;         // Einheit: 1/10 Grad
static double angularSpeed = 0;  // Einheit: Grad / s
/* Fuer eine genaue Berechnung der Winkelgeschwindigkeit werden zwei
 * Zeitintervalle benötigt
 * - Der Zeitintervall, nachdem die Daten aktualisiert werden
 * - Das Zeitintervall zwischen den beiden letzten Phasewechseln
 */ 
static uint32_t tsStartUpdateInterval = 0;
static uint32_t tsOfLastPC = 0;
static int64_t lastPC = 0;       // pc : phasecount

int64_t getAngle(void){
   return 3 * angle;
}

double getAngularSpeed(void){
   return angularSpeed;
}

static void updateAngle(void){
   // 1 tick = 0.3°
	angle = getPhaseCount(NULL);
}

static void updateAngularSpeed(int64_t pc1, int64_t pc2, double interval){
   // Berechnung der Winkelgeschwindigkeit in °/s
   // 1 Phasenwechsel = 0.3°
   angularSpeed = (double) (pc2 - pc1) * (double) 0.3;
   angularSpeed = angularSpeed / interval;
}

#define UPDATE_INTERVAL_IN_S   ((double)0.25)

void initUpdate(void){
   angle = 0;
   angularSpeed = 0;
   tsStartUpdateInterval = currentTimeStamp();   
   lastPC = getPhaseCount(&tsOfLastPC);   
}

void updateUpdate(void){
   // Dieser Berechnung berücksichtig nicht den Fall, dass waehrend des Zeitintervalls
   // die Drehrichtung wechselt. Aufgrund der Groesse des Zeitintervalls ist dies o.k.
	
   // Wichtig ist, dass das Zeitintervall zur Messung der Winkelgeschwindigkeit von Phasenwechsel
   // zu Phasenwechsel geht.
   // Daher warte die Funktion bis zu 2 * UPDATE_INTERVAL_IN_US auf einen Phasewechsel,
   // wenn im Zeitintervall UPDATE_INTERVAL_IN_US mindestens ein Phasenwechsel vorlag.
   
   
   // Erkennung eines Phasewechsel durch Vergleich mit dem aktuellen PhaseCount
      
   uint32_t actTs;
   int64_t curPC = getPhaseCount(&actTs);
   // Test, ob das Zeitfenster eine Messung vergangen ist. Ggf verlängern, bis Phasenwechsel vorliegt
   double timeInterval  = timerDiffToSec(tsStartUpdateInterval, currentTimeStamp());
   
	if ((UPDATE_INTERVAL_IN_S < timeInterval) && ((curPC != lastPC) || (2*UPDATE_INTERVAL_IN_S < timeInterval)) ){
		 // aktuelle Winkel und Winkelgeschwindigkeit und Intervall für Zeitmessung
       tsStartUpdateInterval = currentTimeStamp();
       updateAngle();    
       updateAngularSpeed(lastPC, curPC, timerDiffToSec(tsOfLastPC, actTs));
       update_dddiff(curPC - lastPC, actTs - tsOfLastPC);
       tsOfLastPC = actTs;
       lastPC = curPC;
   }
}

// EOF
