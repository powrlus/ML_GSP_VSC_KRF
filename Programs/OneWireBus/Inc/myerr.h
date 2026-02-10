/**
  * @file myerr.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header file for common error handling. 
  */
#ifndef _MYERR_H
#define _MYERR_H
#include <stdbool.h>

// negativ return values defines error
#define EOK						                   0
#define TIMING_ERR                      -1
#define RESET_ERR                       -2
#define CRC_ERR                         -3
#define SCAN_BUS_ERR                    -4
#define WRONG_PIN_NO                    -5

bool setError(bool cond, char *file, int line, int errVal);
#define ERR_HANDLER(cnd,err) setError((cnd),__FILE__,__LINE__,(err))

void resetError(void);

void printError(void);
#endif
// EOF
