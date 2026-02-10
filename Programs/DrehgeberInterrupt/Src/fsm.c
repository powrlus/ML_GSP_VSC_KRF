/**
  * @file fsm.c
  * @author Franz Korf, HAW Hamburg 
  * @date October 2016
  * @brief Implementation of finite state machine module. 
  */
  
#include "fsm.h"
#include "input.h"
#include "output.h"
#include "timecalc.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "lcd.h"

/*
 * Dieses Modul realisiert die FSM, der Zustand nur die aktuelle Phase ist. Drehrichtung und 
 * Fehler sind in separaten Variablen gespeichert.
 *
 * Es werden Optimierungen f�r eine schnelle Ausf�hrung der ISRs durchgef�hrt. Sie k�nnen nicht 
 * auf die Polling Variante �bertragen werden, da sie u.a. darauf ber�hen, dass beim 
 * Aufruf der ISR ein Phaaenwechsel vorliegt.
 */
 
// Assign these constants to enum values for speeding up phaseCount calculation in ISR 
typedef enum {Backward = -1, Unknown = 0, Forward = 1} RotationType;

static const RotationType updateRotation[4][4] = { // 1. dimension : old phase, 2. dimension: new phase
	     /*             PhaseA,   PhaseD,   PhaseB,   PhaseC */
       /* PhaseA */ { Unknown,  Backward, Forward,  Unknown  },
       /* PhaseD */ { Forward,  Unknown,  Unknown,  Backward },
       /* PhaseB */ { Backward, Unknown,  Unknown,  Forward  },
       /* PhaseC */ { Unknown,  Forward,  Backward, Unknown  }};
			 
static volatile RotationType rotation = Unknown;
static volatile PhaseType curPhase; // wird von initFSM initialisiert
static volatile uint32_t tsLastPhaseChange = 0;
static volatile int64_t phaseCount = 0;
static volatile bool err = false;

int64_t getPhaseCount(uint32_t *ts){
   for(int timeOut = 0; timeOut < 10; timeOut++) {
      uint32_t t1 = tsLastPhaseChange;
      int64_t pc1 = phaseCount; 
      uint32_t t2 = tsLastPhaseChange;
      int64_t pc2 = phaseCount; 
      if ((t1 == t2) && (pc1 == pc2)) {
         // keine Unterbrechung durch ISR waehrend t1 und pc1 gelesen wurden
				 if (ts != NULL) {
            *ts = t1;
				 }
				 // in case of error: return 0 as phase count
				 // This will be done here, to avoid reduce ISR code 
         return (err) ? 0 : pc1;
      }
   }
   lcdGotoXY(3,3);
   lcdPrintlnS("INTERNAL ERROR: ISR to fast."); 
	 while (!err) {
		 err = true;
	 }
   return 0;
	 
}

void resetFSM(void){
   rotation = Unknown;
   phaseCount = 0;
   err = false;
   tsLastPhaseChange = currentTimeStamp();
}

void initFSM(PhaseType phase){
   resetFSM();
   curPhase = phase;

   // Setup Interrupt Controller 16 Proioritaeten, 0 hoechste Prioritaet
   // Subpriorities werden hier nicht verwenden. 
   // Group Priority ist schon entsprechend eingestellt 
   NVIC_SetPriority(EXTI0_IRQn, 0x00); // Setze auf hoechste Prioritaet 0
   NVIC_EnableIRQ(EXTI0_IRQn);         // Enable IRQ
   NVIC_SetPriority(EXTI1_IRQn, 0x00); // Setze auf hoechste Prioritaet 0
   NVIC_EnableIRQ(EXTI1_IRQn);         // Enable IRQ
	   
	 EXTI->IMR |= (1<<0);  // Unmask Int0		
   EXTI->IMR |= (1<<1);  // Unmask INT1
}

bool inErrorState(void){
   return err;
}

bool forwardRotation(void) {
	 return Forward == rotation; 
}

bool backwardRotation(void) {
	 return Backward == rotation; 
}

// Diese Funktion kann nicht f�r die Polling Varianten verwendet werden,
// da sie darauf basiert, dass sie nur in der ISR aufgerufen wird und somit 
// ein Phasenwechsel vorliegt.
static inline void changeState(PhaseType phase){  // Cannot be used for Polling version
	 rotation = updateRotation[curPhase][phase];
   err = err || (rotation == Unknown); 
	 // In case of err, getPhaseCount returns a phase count of 0.
	 // This speeds up ISR, since err must not be checked here for assigning 0 to phaseCount
	 phaseCount = phaseCount + rotation;
	 curPhase = phase;
} 

void EXTI0_IRQHandler(void){ 
   setLED_GPIOG_2(true);
   tsLastPhaseChange = currentTimeStamp();
   EXTI->PR = (1<<0); // Reset INT0
   changeState(giveCurrentPhase());
   setLED_GPIOG_2(false);
}

void EXTI1_IRQHandler(void){
   setLED_GPIOG_2(true);
   tsLastPhaseChange = currentTimeStamp();
   EXTI->PR = (1<<1); // Reset INT1
   changeState(giveCurrentPhase());
   setLED_GPIOG_2(false);
}

// EOF
