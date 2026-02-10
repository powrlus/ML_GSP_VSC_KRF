/*
  ******************************************************************************
  * @file    	oneWireBus.h
  * @author  	Franz Korf
  *        	    HAW-Hamburg
  *          	Labor fuer technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    2016-04-29
  * @brief   This module implements basic access functions for oneWireBus
******************************************************************************  */
#ifndef _ONEWIREBUS_H
#define _ONEWIREBUS_H

#include <stdint.h>
#include <stdbool.h>

#define PDROM_SIZE     			8
#define SCRATCHPADSIZE    	9

#define READ_ROM_CMD      	0x33
#define READ_SCP_CMD      	0xBE
#define MATCH_ROM_CMD     	0x55
#define SKIP_ROM_CMD      	0xCC
#define CONVERT_T_CMD     	0x44

typedef uint64_t  PDROM;  // CRC Byte SERNo_BIT_47 ... Byte SERNo_BIT_0 FamilyCode

 /**
 * @brief This functions gives the family code of of PDROM entry
 *
 * @param pdrom PDROM entry
 *
 * @return Family coe
 */
uint8_t getFamilyCode(uint64_t pdrom); 

/**
 * @brief Initialize one wire bus interface
 */
 void oneWireBusInit(void);
 
 /**
 * @brief Write one bit to oneWireBus
 *
 * @param val The value of the bit that should be written to the bus
 */
void writeBit(unsigned char val);
	 
 /**
 * @brief Write one byte to the oneWireBus
 *
 * @param val The byte that should be written to the oneWireBus.
 */
void writeByte(unsigned char val);

 /**
 * @brief Write a sequence of bytes to the oneWireBus
 *
 * @param buf Sequence of bytes that should be written.
 *            buf[0] is the MSB - the last byte that should be written
 * @param size Number of bytes that should be written
 */
void writeByteSeq(unsigned char * buf, unsigned int size);

/**
 * @brief Write one bit to oneWireBus
 *
 * @retval Value of the bit that has been read.
 */
unsigned char readBit(void);

/**
 * @brief Read one byte from the oneWireBus
 *
 * @return The byte that has been read 
 */
unsigned char readByte(void);

 /**
 * @brief Read a sequence of bytes from oneWireBus
 *
 * @param buf Buffer for bytes that have been read.
 *            buf[0] is the MSB - the last byte that has been read
 * @param size Number of bytes that should be written
 *
 * @retval Result of CRC check of buf
 */
bool readByteSeq(unsigned char * buf, unsigned int size);

/**
 * @brief Resets temperatur sensors on oneWireBus
 *
 * @retval true on success, otherwise false
 */
bool resetBus(void);

/**
 * @brief This functions energize the one wire bus 
 *
 * @param t Periode of time for energizing the bus.
 */
void energizeBus(uint32_t t);

/**
 * @brief This functions reads 8 byte form one wire bus.
 *        They will be interpreted as product data ROM
 *
 * @retval product data ROM
 */
PDROM readRomData(void);

/**
 * @brief This functions writes product data ROM to one wire bus.
 *
 * @param The rom that should be written
 */
void writeRomData(PDROM rom);

PDROM giveTestRomData(void);

#endif // _ONEWIREBUS_H
// EOF
