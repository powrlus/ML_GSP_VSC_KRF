/**
 *******************************************************************
 * @file    input.c 
 * @author  Franz Korf
 *        	HAW-Hamburg
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @date    WS 2016
 * @brief   Implementation of module input
 *******************************************************************
*/

#include "input.h"

#define INPUT_REG							            GPIOF

#define OFFSET_ERROR_RESET_BUTTON			      6

#define ERROR_RESET_BUTTON_MASK					   (0x01 << OFFSET_ERROR_RESET_BUTTON)

bool errorResetButtonPressed(void){
   return 0x0000 == (INPUT_REG->IDR & ERROR_RESET_BUTTON_MASK);
}

void initInput(void){
	// Setup Routing of interrupt (connected to INT0 and INT1 on ITS Board
	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; //Clock for GPIO Port G	
   RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //Clock for Syscfg
	
   // Connect EXTI0 with Pin 0 of GPIO G (MASK0x6)
   SYSCFG->EXTICR[0] &= ~(0xf << (4*0)); //Remove old selection
   SYSCFG->EXTICR[0] |= 0x6 << (4*0); //Select Port G   
   EXTI->RTSR |= (1<<0); //select rising trigger for INT0    
   EXTI->FTSR |= (1<<0); //select falling trigger for INT0    

   // Connect EXTI1 with Pin 1 of GPIO G (MASK0x6)
   SYSCFG->EXTICR[0] &= ~(0xf << (4*1)); //Remove old selection
   SYSCFG->EXTICR[0] |= 0x6 << (4*1); //Select Port G    
   EXTI->RTSR |= (1<<1); //select rising trigger for INT1    
   EXTI->FTSR |= (1<<1); //select falling trigger for INT1
}

// EOF
