/**
  * @file myerr.c
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief This modules implemets a simple error return mechanism using 
	*        the global variable error. 
	*
  */

#include "myerr.h"
#include "TFTOutput.h"
#include "stdio.h"

static int error = EOK;
static int errLine = -1;
static char * errFile = NULL;

bool setError(bool cond, char *file, int line, int errVal) {
   bool err = (cond);
   if (err && (error == EOK)) {
      error = errVal;
      errLine = line;
      errFile = file;
   }
   return err;   
}

void resetError(void) {
   error = EOK;
   errLine = -1;
   errFile = NULL;
}

void printError(void){
   if (error != EOK){
      showError(errFile, errLine, error);
   }
}

// EOF
