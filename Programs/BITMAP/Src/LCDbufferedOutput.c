/**
 ******************************************************************************
 * @file    LCDbufferedOutput.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 0.8
 *
 * @date    6. 11. 2022
 * @brief   Buffer Konzept, dass eine ganze Zeile aus einen internen Buffer
 *          auf das LCD Display  geschrieben.
 *          Signifikate Geschwindigkeitssteigerung gegenüber Pixel-weiser
 *          Ausgabe.
 *          Der Ansatz geht davon aus, dass die Pixel zeilenweise ausgegeben
 *          werden.
 *
 ******************************************************************************
 */

#include "LCDbufferedOutput.h"
#include "LCD_GUI.h"
#include "colorTable.h"

static POINT curX = 0;

static COLOR lineBuf[LCD_X_MAXPIXEL];

void initPrintBuf(void){
   curX = 0;
}

void setPixelOutputBuf(int x, unsigned char red, unsigned char green, unsigned char blue){
   RGBTRIPLE col = {.rgbtBlue = blue, .rgbtGreen = green, .rgbtRed = red};
   lineBuf[x] = RGB2LCDcolor(col);
   curX = x;
}

void flushOutputBuf(int line){
   Coordinate tl = {.x = 0, .y = LCD_Y_MAXPIXEL - 1 - line};
   GUI_WriteLine(tl, curX + 1, lineBuf);
}

// EOF