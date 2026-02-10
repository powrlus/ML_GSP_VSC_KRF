#ifndef _LINEBUFFER_H
#define _LINEBUFFER_H

#include "BMP_types.h"

#define INVALID_BUF_IDX		-1

void initLineBuffer(void);

int getBufIdxOfLine(int line);

int assignLineBuf(int line);

RGBTRIPLE getElem(int bufIdx, unsigned int x);

void setElem(int bufIdx, unsigned int x, RGBTRIPLE col);

#endif
// EOF