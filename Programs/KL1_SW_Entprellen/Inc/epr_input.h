#ifndef EPR_INPUT_H
#define EPR_INPUT_H

#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

#define PORT_SIZE 16
#define READING_ATTEMPTS 10
#define MAX_PRELLZEIT_US 20 * US_PER_MS
#define US_PER_MS 1000
    /*********************************************
    * @brief   Function that reads the value of one gpio pin
    *
    * @arg     port     port of which the pin is read
    *          pinMask  mask with 1 at the pin to read
    *
    * @returns  0 AOK
    *          -2 bitmask invalid
    *          -1 port invalid 
    **********************************************/
    int readPin(GPIO_TypeDef *port, uint16_t pinMask, bool *pPinVal);

        /*********************************************
    * @brief   Function that reads the value of a port
    *
    * @arg     port     port which is read
    *
    * @returns 0  AOK
    *          -1 port invalid 
    **********************************************/
    int readPort(GPIO_TypeDef *port, uint16_t *pPortVal);
#endif
// eof