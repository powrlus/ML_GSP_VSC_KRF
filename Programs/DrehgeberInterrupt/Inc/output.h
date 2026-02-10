/**
  * @file output.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file of  output module. 
  */

#ifndef _OUTPUT_H
#define _OUTPUT_H

#include <stdint.h>
#include <stdbool.h>
#include <stm32f4xx_hal.h>

#define LED_REG_INFO				 GPIOE

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt einen Pins einer GPIO Ports.
 *
 *  @param  port Das GPIO Port, dessen veraendert wird
 *  @param  pin Nummer des Pins
 *  @param  switchOn <=> Der pin wird auf high gesetzt
 *
 *  @return void
 ****************************************************************************************/
static inline void setPin(GPIO_TypeDef *port, unsigned char pin, bool switchOn) {
   port->BSRR = (0x01 << (pin + (switchOn ? 0 : 16)));
}

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die 8 LEDs zur Ausgabe des Pulszaehlers.
 *
 *  @param  val Bitmuster, das ausgegeben wird.
 *
 *  @return void
 ****************************************************************************************/
void setCounterLEDs(const uint8_t val) ;

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die Error-LED.
 *
 *  @param  on <=> Error-LED wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setErrorLED   (bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die LED zur Anzeige der Drehrichtung vorwerts.
 *
 *  @param  on <=> Forward-LED wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setForwardLED (bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die LED zur Anzeige der Drehrichtung rueckwerts.
 *
 *  @param  on <=> Backward-LED wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
void setBackwardLED(bool on);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion set LED1 zur Zeitmessung.
 *
 *  @param  on <=> LED1 wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
static inline void setLED_GPIOG_1(bool on){ setPin(LED_REG_INFO, 1, on); }

/**
 *****************************************************************************************
 *  @brief  Diese Funktion set LED2 zur Zeitmessung.
 *
 *  @param  on <=> LED2 wird angeschaltet. 
 *
 *  @return void
 ****************************************************************************************/
static inline void setLED_GPIOG_2(bool on){ setPin(LED_REG_INFO, 2, on); }

#endif
//EOF
