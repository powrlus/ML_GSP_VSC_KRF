/*
  ******************************************************************************
  * @file    	scanBus.c
  * @author  	Franz Korf
  *        	    HAW-Hamburg
  *          	Labor fuer technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    2016-11-20
  * @brief   This module scane one wire bus for sensors connected to it
******************************************************************************  */
#include "scanBus.h"
#include "oneWireBus.h"
#include "myerr.h"

#define SEARCH_ROM_CMD     	0xF0

#define MAX_NUMBER_PDROMS		10
static PDROM pdromList[MAX_NUMBER_PDROMS];
static unsigned char nextFreeEntryInPDROMList = 0;

static void resetPdromList(void){
   nextFreeEntryInPDROMList = 0;
}

static bool addToPdromList(PDROM rom){
   if (MAX_NUMBER_PDROMS == nextFreeEntryInPDROMList){
      return false;
   }
	pdromList[nextFreeEntryInPDROMList++] = rom;
	return true;
}

unsigned char giveNumberOfPDROMS(void){
   return nextFreeEntryInPDROMList;
}

PDROM givePDROM(unsigned char n){
   if (n < nextFreeEntryInPDROMList){
      return pdromList[n];
	}
	return 0x00;
}

enum AdressBitCombis {allZero=0x01, allOne=0x02, oneAndZero=0x00, busBroken=0x03}; // Codierung wichtig, sonst rechnet readNextAdrBit falsch

static enum AdressBitCombis readNextAdrBit() {
	unsigned char bit = readBit() << 1;
	unsigned char invBit = readBit();
	return bit | invBit;
}

static bool isOne(int pos, PDROM rom){
   PDROM mask = (((uint64_t) 0x01) << pos);	
	return mask == (mask & rom);
}

/**
  * @brief  Diese Funktion schreibt das gewählte Bit für den ROM Scan auf den Bus,
  *         aktualisiert das entsprechende Bit im ROM und testet, ob der geschriebene
  *         Wert mit den des ROM übereinstimmt.
  * @param  pos  Bit in ROM, das geschriebenen wird
  * @param  val  Wert des Bits: 0, 1 : schreibe 0 bzw. 1 , sonst schreibe Wert, der im ROM 
  *              an der Bit Position steht.
  * @param  rom  Aktuelle ROM Wert
  * @retval Geschriebenes Bit stimmt mit Bit im ROM überein
  */
static bool setBit(int pos, char val, PDROM *rom){
   if ((0 > pos) || (pos > 63)){
      while(1) ;
   }
	val = ((val != 0) && (val != 1)) ? isOne(pos,*rom) : val;		 
	writeBit(val);
	bool erg = (0 == val) == !isOne(pos, *rom);	  
	if (val) {
      *rom = *rom | (((uint64_t) 0x01) << pos);
	} else {
		*rom = *rom & ~(((uint64_t)0x01) << pos);
	}
	return erg;
 }	 

// Iterative Lösung, die alle ROMs auf dem Bus sucht
// Rekursive Variante fuehrt zum Stack Overflow
static bool searchROMs(void) {
   int pos0selected = -1;  // Letzte (hinterste) Position in der ROM Adresse, an der zwischen 
                           // 1 und 0 gewählt werden konnte und 0 gewählt wurde
	int posSelect1   = -1;  // Position, an der zwischen 0 und 1 gewählt werden, bei letzten
	                        // mal eine 0 gewählt wurde und nun eine 1 gewählt werden sollen.
	                        // Das ist der Wert von selcted0 des vorherigen Durchlaufs
	// Ab der Position select1 + 1, wird bei Alternativen immer die 0 gewählt.
 	// Bis zur Position select1-1 wird bei einer Alternativen immer der Wert aus dem letzten 
	// Durchlauf gewählt.
	PDROM romAdr = 0;
	do {
      pos0selected = -1;
		// start ROM Scan
		if (ERR_HANDLER(!resetBus(), SCAN_BUS_ERR)){
         return false;
	   }
	   writeByte(SEARCH_ROM_CMD);
      // find  next ROM
		for(int pos = 0; pos < 64; pos++){
         enum AdressBitCombis v = readNextAdrBit();
         if (ERR_HANDLER(busBroken == v, SCAN_BUS_ERR)){
            return false;
         }
         if ((allOne == v) || (allZero == v)){
            if (ERR_HANDLER(!setBit(pos, allOne == v, &romAdr) && (posSelect1 >= pos), SCAN_BUS_ERR)){						 
               return false;
            }
         }
         if (oneAndZero == v){
            if (pos >= posSelect1){
               setBit(pos, pos == posSelect1, &romAdr);
            } else {
               setBit(pos, 2, &romAdr);
            }
            pos0selected = !isOne(pos, romAdr) ? pos : pos0selected;
         }
      }
      // write ROM adr to data bus
		if (!addToPdromList(romAdr)){
         return false;
      }
      posSelect1 = pos0selected;
   } while (pos0selected != -1);
   return true;
}


bool scanPDROMS(void){
   resetPdromList();
   return searchROMs(); 
}

// EOF
