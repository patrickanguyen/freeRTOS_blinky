// Header:
// File Name: 
// Author:
// Date:
#ifndef BSP_H
#define BSP_H

#include "FreeRTOS.h"

/* 
** Initalization functions 
** Make sure that functions are run 
** before accessing registers
*/
void PortF_Init(void) ;
void ButtonLEDInit(void);

/* 
* Make sure blinky functions are run in critical section 
* to avoid race conditions
*/
void toggleRedLED(void);
void toggleBlueLED(void);
void toggleGreenLED(void);
void toggleButtonLED(void);


BaseType_t checkButton(void);
#endif
