#include "colorTable.h"
#include "errorhandler.h"
#include "input.h"
#include "headers.h"
#include <stdbool.h>

static RGBTRIPLE colorTable[MAX_COLOR_TABLE_SIZE];
static bool validColorTable = false;
static int tableSize = 0;  // 0 : MAX_COLOR_TABLE_SIZE entries

int readColorTable(){
   validColorTable = false; // init color table
   tableSize = 0;
   BITMAPFILEHEADER fh;
   BITMAPINFOHEADER ih;
   
   RAISE_NOK(getFileHeader(&fh));
   RAISE_NOK(getInfoHeader(&ih));

   if (fh.bfOffBits <= (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))) {
      // No color palette in file
      return EOK;
   }
   
   RETURN_NOK_ON_ERR((ih.biBitCount != 8) || (ih.biClrUsed > MAX_COLOR_TABLE_SIZE), "readColorTable: invalid header data.");
   // Read color palette
   tableSize = (0 == ih.biClrUsed) ? MAX_COLOR_TABLE_SIZE : (int)ih.biClrUsed;
   
   for (int i = 0; i < tableSize; i++){
      RGBQUAD col;
      RETURN_NOK_ON_ERR(1 != COMread((char *) &col, sizeof(RGBQUAD), 1), "readColorTable: Error during read.");
      colorTable[i].rgbtBlue = col.rgbBlue;
      colorTable[i].rgbtRed = col.rgbRed;
      colorTable[i].rgbtGreen = col.rgbGreen;	 
   }
   validColorTable = true;
   return EOK;
}

int getColor(unsigned char index, RGBTRIPLE *col){
   RETURN_NOK_ON_ERR(!validColorTable,"getColor: invalid color table.");
   RETURN_NOK_ON_ERR(index >= tableSize, "getColor: invalid index.");
   *col = colorTable[index];
   return EOK;
}

COLOR RGB2LCDcolor(RGBTRIPLE col){
   // Vermutung Farbcodierung in 16 Bits, von links nach rechts: 5 Bits Rot 6 Bits gruen 5 bits blau
   COLOR bluePart  = ((COLOR)(col.rgbtBlue >> 3)) & 0x1F;
   COLOR greenPart = (((COLOR)(col.rgbtGreen >> 2))<<5) & 0x07E0;
   COLOR redPart   = (((COLOR)(col.rgbtRed >> 3))<<11) & 0x0F800;
	return redPart | greenPart | bluePart;
}

// EOF
