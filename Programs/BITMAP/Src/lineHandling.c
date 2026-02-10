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
 *          Der Puffer geht davon aus, dass Zeilen und Spalten in aufsteigender
 *          Reihenfolge befüllt werden.
 *
 ******************************************************************************
 */

#include "lineHandling.h"
#include "main.h"
#include "lineBuffer.h"
#include "colorTable.h"
#include "errorhandler.h"
#include <math.h>
#include "LCDbufferedOutput.h"

static int nextOutputLine = 0; // next line that should be written to LED
static LONG picWidth, picHeight;
static int boxSize = 0;
static float scale = 0;

void initLineHandling(LONG biWidth, LONG biHeight){
   picWidth = biWidth;
   picHeight = biHeight;
   nextOutputLine = 0;
   if ((picHeight <= LCD_Y_MAXPIXEL) && (picWidth <= LCD_X_MAXPIXEL)) {
      boxSize = 1;
      scale = 1;
   } else { 
      scale = MIN(LCD_X_MAXPIXEL/(float)picWidth, LCD_Y_MAXPIXEL/(float)picHeight);
      boxSize = ceil(1/scale);
   }
   initLineBuffer();
}

static void printLine(void){
   int bufArr[MAX_SCALE]; 
   // All lines must be completely filled.
   int y_ = floor(nextOutputLine/scale); // lowest line in picture
   if (nextOutputLine != 0) {
      // check, if line must be printed to due scaling
      int y_end_old = MIN(floor((nextOutputLine-1)/scale) + boxSize - 1, picHeight - 1);
      if ((y_ >= picHeight) || ((y_ == picHeight-1) && (y_end_old == (picHeight-1)))){
         return;
      }
   }
   // nextOutputLine must be printed due to scaling factor
   // check and select buffers of lines
   int y_end = MIN(y_ + boxSize - 1, picHeight - 1);
   for (int i = y_; i <= y_end; i++){
      bufArr[i-y_] = getBufIdxOfLine(i);
      if (INVALID_BUF_IDX == bufArr[i-y_]){
         return; // not all lines in buffer
      }
   }
   // scale line and print
   int x_end = 0;
   int x = 0;
   for (x = 0; x < LCD_X_MAXPIXEL; x++){
      int x_ =floor(x / scale);
      if ((x_ >= picWidth) || ((x_ == picWidth - 1) && (x_end == picWidth - 1))){
         break;
      }
      // min() is used to assure that coordinates aren't out of bounds
      x_end = MIN(x_ + boxSize - 1, picWidth - 1);
      // average of pixel
      unsigned int red = 0, blue = 0, green = 0;
      for (int i = 0; i <= y_end - y_; i++){
         for(int j = x_; j <= x_end; j++) {
            RGBTRIPLE c = getElem(bufArr[i],j);
            red = red + c.rgbtRed;
            blue = blue + c.rgbtBlue;
            green = green + c.rgbtGreen;
         }
      }
      red = red /((y_end - y_ + 1) * (x_end - x_ + 1));
      blue = blue /((y_end - y_ + 1) * (x_end - x_ + 1));
      green = green /((y_end - y_ + 1) * (x_end - x_ + 1));
      setPixelOutputBuf(x, red, green, blue);
   }
   flushOutputBuf(nextOutputLine++);
}

void setPixel(LONG x, unsigned int y, RGBTRIPLE col){
   LOOP_ON_ERR(MAX_PIC_WIDTH <= x, "setPixel: column not in buffer.");
   LOOP_ON_ERR(MAX_PIC_HEIGHT <= y, "setPixel: line not in buffer.");
   int idx = getBufIdxOfLine(y);	
   if (INVALID_BUF_IDX == idx){
      idx = assignLineBuf(y);
   }
   setElem(idx, x, col);
   if (picWidth ==  x + 1){
      // last Pixel of line updated
      printLine();
   }
}

// EOF
