#ifndef _LCDBUFFERDOUTPUT_H
#define _LCDBUFFERDOUTPUT_H

void initPrintBuf(void);

void setPixelOutputBuf(int x, unsigned char red, unsigned char green, unsigned char blue);

void flushOutputBuf(int line);

#endif
// EOF