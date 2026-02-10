
#include "uncompressedBMP.h"
#include "BMP_types.h"
#include "errorhandler.h"
#include "lineHandling.h"
#include "headers.h"
#include "input.h"
#include "main.h"
#include "colorTable.h"

static int readNextUncompressedLine(int line, LONG lineWidth, WORD bitCount){
   for(int i = 0; i < lineWidth; i++){
      RGBTRIPLE col;
      if (24 == bitCount){
         RETURN_NOK_ON_ERR(1 != COMread((char *) &col, sizeof(RGBTRIPLE), 1), "readNextUncompressedLine: Error during read.");
      } else {
         unsigned char c;
         RETURN_NOK_ON_ERR(1 != COMread((char *) &c, sizeof(unsigned char), 1), "readNextUncompressedLine: Error during read.");
         RAISE_NOK(getColor(c, &col));
      }
      setPixel(i, line, col);
   }
   return EOK;
}

#define PADDING_BYTES_OF_ROW(w,c) (((((w) * (c) + 31)/32) * 4)  - ((w) * (c) / 8))

int printUncompressedBitMap(void){
   BITMAPINFOHEADER ih;
   RAISE_NOK(getInfoHeader(&ih));
   int padding = PADDING_BYTES_OF_ROW(ih.biWidth, 8);
	
   for(int line = 0; (line < ih.biHeight); line++){
      RAISE_NOK(readNextUncompressedLine(line, ih.biWidth, ih.biBitCount));   // Problem: langsam
      for (int i = 0; i < padding; i++){ 
         nextChar();
      }
   }
   return EOK;
}

// EOF