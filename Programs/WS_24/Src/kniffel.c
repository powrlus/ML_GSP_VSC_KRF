/**
 ******************************************************************************
 * @file    kniffel.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    20. Jan. 2025
 * @brief   Dieses Modul speichert den Zustand der W�rfel.
 *
 ******************************************************************************
 */
#include "kniffel.h"
#include "error.h"
#include "main.h"
#include "random.h"
#include <stdint.h>
#include <stdlib.h>

#define IDX_FORWARDACCESS 1 

struct dieInfo{
    uint8_t value;
    bool isFixed;
};

static struct dieInfo dice[NO_DICE]; 

uint8_t getDie(uint8_t die) {
    if (die > NO_DICE || die < 0) {
        return 0;
    }

    return dice[die].value;
}

bool isKniffel() {
    bool kniffel = true;

    for(int i = 0; i < (NO_DICE - IDX_FORWARDACCESS); i++) {
        if (dice[i].value != dice[i + IDX_FORWARDACCESS].value) {
            kniffel = false;
        }
    }
    return kniffel;
}

bool isStreet() {
    
    bool street = true;
    
    if (dice[0].value > DIE_MAXVAL) {
        Error_Handler();
    }

    if(dice[0].value < 2) {
        street = false;
        return street;
    }

    for(int i = 0; i < (NO_DICE - IDX_FORWARDACCESS); i++) {
        if (dice[i].value != dice[i].value - 1) {
            street = false;
        }
    }
    return street;
}

void fixDie(uint8_t die) {
    if (die > NO_DICE) {
        Error_Handler();
    }
    dice[die].isFixed = true;
}

void releaseDie() {
    for(int i = 0; i < NO_DICE; i++) {
        dice[i].isFixed = false;
    }
}

bool isFixed(uint8_t die) {
    if (die > NO_DICE) {
        Error_Handler();
    }
    return dice[die].isFixed;
}

void rollDice() {
    for(int i = 0; i < NO_DICE; i++) {
        if (!dice[i].isFixed) {
            dice[i].value = nxtRandNumber() + DIE_MINVAL; // MAX_RAND auf 5 für korrekten Wertebereich
        }
    }
}

// EOF