/**
  ******************************************************************************
  * @file    	main.c 
  * 
  * @brief   Implementation eines einfachen Drogentesters.
  ******************************************************************************
  */

 
/* Includes ------------------------------------------------------------------*/
#include <HAW_init.h>
#include "tests.h"
#include "HAW_lcd.h"


/*******************************************************************************
  * @brief  Diese  Funktion implementiert den Tester gemaess DDC.
  *****************************************************************************/

int main(void) {
	
	int i=0;
	HAWInit();
	
	//HAWDisplayStr(2,2,"Hallo");
	
	// testA3();
	// testA4();
	// testA5();
	
	// Initialisierung

	// Zustandvariablen
	
  while (i < 1000) { // DDC
	   // read sensors
		 i += 1;
     // update state
		
		 // calcuate output		 
		 
    // drive output

	}
}
// EOF
