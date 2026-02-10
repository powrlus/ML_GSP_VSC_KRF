#ifndef _LINEHANDLING_H
#define _LINEHANDLING_H

#include "MS_basetypes.h"
#include "BMP_types.h"

extern void initLineHandling(LONG biWidth, LONG biHeight);

extern void setPixel(LONG x, unsigned int y, RGBTRIPLE col);

#endif
// EOF
