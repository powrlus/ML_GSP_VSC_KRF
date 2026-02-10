/*
 * Implementation des hardware abstraction layers.
 *  GS WS 2016
 * Franz Korf
 * file hal.c
 */
#include "hal.h"
#include "myerr.h"

#define CHECK_PIN(pin)   ((0 <= (pin)) && ((pin) <= 15))

void setOutputMode(GPIO_TypeDef* port, const unsigned char pin){
   if (ERR_HANDLER(!CHECK_PIN(pin), WRONG_PIN_NO)) return;
   port->MODER &= ~(0x03 << (2 * pin));  // reset bits
   port->MODER |=  (0x01 << (2 * pin));  // set output mode 01
}

void setOpenDrainMode(GPIO_TypeDef* port, const unsigned char pin){
   if (ERR_HANDLER(!CHECK_PIN(pin), WRONG_PIN_NO)) return;
   port->OTYPER |= (0x01 << pin);
}

void setPushPullMode(GPIO_TypeDef* port, const unsigned char pin){
   if (ERR_HANDLER(!CHECK_PIN(pin), WRONG_PIN_NO)) return;
   port->OTYPER &= ~(0x01 << pin);
}

void writePin(GPIO_TypeDef* port, const unsigned char pin, const unsigned char val){
   if (ERR_HANDLER(!CHECK_PIN(pin), WRONG_PIN_NO)) return;
	port->BSRR = (0x01 << (pin + ((0 != val)? 0 : 16)));
}

int readPin(GPIO_TypeDef* port, const unsigned char pin){
   if (ERR_HANDLER(!CHECK_PIN(pin), WRONG_PIN_NO)) return 0;
	return (port->IDR & (0x01<< pin)) >> pin;
}
// EOF
