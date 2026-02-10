
#include "LCD_GUI.h"

#define MAX_SCALE        5 
#define MAX_PIC_WIDTH    (MAX_SCALE * LCD_X_MAXPIXEL)  // max. picture width 
#define MAX_PIC_HEIGHT   (MAX_SCALE * LCD_Y_MAXPIXEL)  // max. picture height 

#define MAX(x,y)         ((x) < (y) ? (y) : (x))
#define MIN(x,y)         ((x) < (y) ? (x) : (y))