#ifndef _COLORTABLE_H
#define _COLORTABLE_H

#include "BMP_types.h"
#include "LCD_general.h"

extern int readColorTable();

extern int getColor(unsigned char index, RGBTRIPLE *col);

extern COLOR RGB2LCDcolor(RGBTRIPLE col);

#endif
// EOF

