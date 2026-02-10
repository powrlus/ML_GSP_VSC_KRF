/**
 ******************************************************************************
 * @file    lineHandling.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 0.8
 *
 * @date    6. 11. 2022
 * @brief   Das ganze Bild kann nicht gespeichert werden. Daher speichert das
 *          Modul die letzten n Zeilen. n hängt von der maximalen Block Größe  
 *          des Komprimierungsalgorithmus ab.
 *          Der Puffer geht dass die Pixel eine Zeile und die Zeilen selbst 
 *          in aufsteigender Reihenfolge eingefügt werden.
 *
 ******************************************************************************
 */

#include "lineBuffer.h"
#include "main.h"
#include "colorTable.h"
#include "errorhandler.h"

#define NO_LINE_BUFS    (MAX_SCALE)
#define INVALID_LINE		  -1

static struct {
   int lineNo; // line number in buffer ; -1 : invalid buffer
   RGBTRIPLE buf[MAX_PIC_WIDTH];
} lineBufs[NO_LINE_BUFS];

void initLineBuffer(void){
   for(int i = 0; i < NO_LINE_BUFS; i++){
      lineBufs[i].lineNo = INVALID_LINE;
   }
}

int getBufIdxOfLine(int line){
   static int cache = 0;
   if (lineBufs[cache].lineNo == line) { 
      return cache;
   }
   for (int i = 0; i < NO_LINE_BUFS; i++){
      if (lineBufs[i].lineNo == line) {
         cache = i;
         return i;
      }
   }
   return INVALID_BUF_IDX;
}

int assignLineBuf(int line){
   int idx = 0;
   for (int i = 0; i < NO_LINE_BUFS; i++){
      LOOP_ON_ERR(lineBufs[i].lineNo == line, "assignLineBuf: line exists in buffer");
      idx = (lineBufs[i].lineNo < lineBufs[idx].lineNo) ? i : idx;
   }
   lineBufs[idx].lineNo = line;
   return idx;
}

RGBTRIPLE getElem(int bufIdx, unsigned int x){
   LOOP_ON_ERR(MAX_PIC_WIDTH <= x, "getElem: column not in buffer.");
   LOOP_ON_ERR((0 > bufIdx) || (bufIdx >= NO_LINE_BUFS), "getElem: invalid bufIdx.");
   LOOP_ON_ERR(INVALID_LINE == lineBufs[bufIdx].lineNo, "getElem: access to invalid line.");
   return  lineBufs[bufIdx].buf[x]; // this line will never be reached
}

void setElem(int bufIdx, unsigned int x, RGBTRIPLE col){
   LOOP_ON_ERR(MAX_PIC_WIDTH <= x, "setElem: column not in buffer.");
   LOOP_ON_ERR((0 > bufIdx) || (bufIdx >= NO_LINE_BUFS), "setElem: invalid bufIdx.");
   LOOP_ON_ERR(INVALID_LINE == lineBufs[bufIdx].lineNo, "setElem: access to invalid line.");
   lineBufs[bufIdx].buf[x] = col;
}

// EOF