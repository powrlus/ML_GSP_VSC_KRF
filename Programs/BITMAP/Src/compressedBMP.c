#include "compressedBMP.h"
#include "BMP_types.h"
#include "errorhandler.h"
#include "lineHandling.h"
#include "headers.h"
#include "input.h"
#include "main.h"
#include "colorTable.h"
#include "input.h"
#include <stdio.h>

static int lastPrintedx = -1;  // Coordinates of last pixel written to linebuf
static int lastPrintedy =  0;
static RGBTRIPLE bgColor = {0,0,0};

static int readCmd(BYTE *cmdBuf){
   int ch = nextChar();
   RETURN_NOK_ON_ERR(EOF == ch, "readCmd: missing next command.");
   cmdBuf[0] = (char)ch;
   ch = nextChar();
   RETURN_NOK_ON_ERR(EOF == ch, "readCmd: EOF in command.");
   cmdBuf[1] = (char)ch;
   return EOK;
}

static void fillUpCurrentLine(int width){
   for (int i = lastPrintedx + 1; i < width; i++){
      setPixel(i, lastPrintedy, bgColor);
   }
   lastPrintedx = -1;
   lastPrintedy++;
}

static void writePixel2LineBuffer(POINT x, POINT y, RGBTRIPLE col, int width){
   // will unprinted pixel with background Color
   while (lastPrintedy < y){
      fillUpCurrentLine(width);
   }
   for (int i = lastPrintedx + 1; i < x ; i++){
      setPixel(i, y, bgColor);
   }
   setPixel(x, y, col);
   lastPrintedx = x;
   lastPrintedy = y;
}

int printCompressedBipMap(int width) {
   BYTE b[2]; // next compressed command
   int  line = 0; // current line
   int  pos = 0; // current position in line
   lastPrintedx = 0;
   lastPrintedy = 0;
   RGBTRIPLE col;
   
   // parse compessed pixel representation
   while (true){
      // read command
      RAISE_NOK(readCmd(b));
      // parse command b
      if ((0 == b[0]) && (0 == b[1])) { // End of line
         line++;
         pos = 0;
      }
      if ((0 == b[0]) && (1 == b[1])) { // End of bit map
         fillUpCurrentLine(width);
         // skip rest of file
         while(EOF != nextChar()){};  
         return EOK;
      }
      if ((0 == b[0]) && (2 == b[1])) {// Jump to according horizontal and vertical offsets
         BYTE offset[2] = {0,0};
         RAISE_NOK(readCmd(offset)); 
         line = line + offset[0];
         pos = pos + offset[1];
      }
      // following commands read pixel
      if ((0 == b[0]) && (2 < b[1])) { // absolute mode
         int numberOfPixels = (int) b[1];
         for (int i = 0; i < numberOfPixels; i++) {
            int ch = nextChar();
            RETURN_NOK_ON_ERR(EOF == ch, "printCompressedBipMap: missing data");
            RAISE_NOK(getColor((char) ch, &col));
            writePixel2LineBuffer(pos, line, col, width);
            pos++;
         }
         if (1 == numberOfPixels%2) {
            // odd number of pixels, read one spare byte due to word boundary alignment
            RETURN_NOK_ON_ERR(EOF == nextChar(), "printCompressedBipMap: missing data");
         }
      }
      if (0 < b[0]) { // Encoded Mode
         int numberOfPixels = (int) b[0];
         for (int i = 0; i < numberOfPixels; i++) {
            RAISE_NOK(getColor(b[1], &col));
            writePixel2LineBuffer(pos, line, col, width);
            pos++;
         }
      }
   } // end of while loop
   return EOK;
}

// EOF