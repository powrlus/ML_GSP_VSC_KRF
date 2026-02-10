/*
 * Hardware Abstaction Layer GS WS 2016
 * Franz Korf
 * file hal.h
 */
 
#ifndef _HAL_H
#define _HAL_H

#include "stm32f4xx_hal.h"

/**
 * @brief Set  pin of port to output mode
 *
 * @param port Selected port
 * @param pin Pin of selected port
 */
void setOutputMode(GPIO_TypeDef* port, const unsigned char pin);

/**
 * @brief Set  pin of port to open drain mode
 *
 * @param port Selected port
 * @param pin Pin of selected port
 */
void setOpenDrainMode(GPIO_TypeDef* port, const unsigned char pin);

/**
 * @brief Set pin of port to push pull mode
 *
 * @param port Selected port
 * @param pin Pin of selected port
 */
void setPushPullMode(GPIO_TypeDef* port, const unsigned char pin);

/**
 * @brief Drive pin of port with val
 *
 * @param port Selected port
 * @param pin Pin of selected port
 * @param val If val == 0 drive the port with 0 Volt. Otherwise it will
 *            be driven with Vcc
 */
void writePin(GPIO_TypeDef* port, const unsigned char pin, const unsigned char val);

/**
 * @brief Drive pin of port with val
 *
 * @param port Selected port
 * @param pin Pin of selected port
 *
 * @retval value that has been read from bus
 */
int readPin(GPIO_TypeDef* port, const unsigned char pin);

#endif
