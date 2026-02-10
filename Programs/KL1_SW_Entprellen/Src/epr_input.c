#include "epr_input.h"
#include "epr_error.h"
#include "epr_timer.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

    
    int readPin(GPIO_TypeDef *port, uint16_t pinMask, bool *pPinVal) {
    
        int err = AOK;

        int bitCount = 0; 
        for(int i = 0; i < PORT_SIZE; i++) {
            bitCount = ((1 << i) & pinMask) ? (bitCount + 1) : bitCount;
        }

        if (bitCount == 1) { // one pin is masked
            err = INVALID_PINMASK;
            return err;
        }

        for (int i = 0; i < READING_ATTEMPTS; i++) {
            int v1 = (port->IDR & pinMask);            
            
            wait(MAX_PRELLZEIT_US);
            int v2 = (port->IDR & pinMask);
            if (v1 == v2) {
                *pPinVal = (v1 > 0); // 1 wenn pin gesetzt
                return err;
            }
        }

        err = READ_UNSUCCESSFUL;
        return err;
    }
    int readPort(GPIO_TypeDef *port, uint16_t *pPortVal){
        int err = AOK;

        for (int i = 0; i < READING_ATTEMPTS; i++) {
            uint16_t v1 = (uint16_t) port->IDR;            
            
            wait(MAX_PRELLZEIT_US);
            uint16_t v2 = (uint16_t) port->IDR;
            if (v1 == v2) {
                *pPortVal = v2; // pin ist gesetzt
                return err;
            }
        }

        err = READ_UNSUCCESSFUL;
        return err;
    }