#ifndef EPR_TIMER_H
#define EPR_TIMER_H
#include <stdint.h>
/*
*   @brief  this function initialises the functionality of the EprTimer Module and the ITS-Board Timer.
*/
void initEprTimer();
/*
*   @brief This function implements waiting for a specified ammount of time
*
*   @args ms    ammount of time to wait in milliseconds
*/
void wait(uint32_t us);

#endif
//eof