/**
  * @file output.c
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Dieses Modul treibt die GPIO Ausgaben. 
	*
  */

#include "output.h"

#define LED_REG_COUNTER				 GPIOD

#define OFFSET_ERROR_LED			    5
#define OFFSET_BACKWARD_LED       6
#define OFFSET_FORWARD_LED		    7
#define OFFSET_COUNTER_LEDS       0

void setCounterLEDs(const uint8_t val) {
	 // read modify write required
	 const uint32_t mask = (0xFF << OFFSET_COUNTER_LEDS);
	 uint32_t  currentValue = LED_REG_COUNTER->ODR;
	 currentValue &= ~mask;
	 currentValue |= (((uint32_t) val) << OFFSET_COUNTER_LEDS);
	 LED_REG_COUNTER->ODR = currentValue;
}


void setErrorLED(bool on){
   setPin(LED_REG_INFO, OFFSET_ERROR_LED, on);
}

void setForwardLED(bool on){
   setPin(LED_REG_INFO, OFFSET_FORWARD_LED, on);
}

void setBackwardLED(bool on){
   setPin(LED_REG_INFO, OFFSET_BACKWARD_LED, on);
}



//EOF
