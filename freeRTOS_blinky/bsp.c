#include "bsp.h"
#include "TM4C123GE6PM.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define BUTTON_PIN (1U << 4)
#define BUTTON_LED (1U << 5)


void PortF_Init(void) 
{
    unsigned long volatile delay_clock;
    SYSCTL->RCGCGPIO |= (1U << 5U);
    delay_clock = SYSCTL->RCGCGPIO;
    (void) delay_clock;
    SYSCTL->GPIOHBCTL |= (1U << 5U);
    
    
    /* Initalize PORTF (1-3) as GPIO Digital Output */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->AMSEL &= ~(LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->PCTL &= ~(LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->AFSEL &= ~(LED_RED | LED_BLUE | LED_GREEN);
    
    /* Initalize PORTF 0 as GPIO Digital Input */
    GPIOF_AHB->DIR &= ~BUTTON_PIN;
    GPIOF_AHB->DEN |= BUTTON_PIN;
    GPIOF_AHB->AMSEL &= ~BUTTON_PIN;
    GPIOF_AHB->PCTL &= ~BUTTON_PIN;
    GPIOF_AHB->AFSEL &= ~BUTTON_PIN;
    GPIOF_AHB->PUR |= BUTTON_PIN;
    
}

void ButtonLEDInit(void)
{
    unsigned long volatile delay_clock;
    SYSCTL->RCGCGPIO |= (1U << 1U);
    delay_clock = SYSCTL->RCGCGPIO;
    (void) delay_clock;
    SYSCTL->GPIOHBCTL |= (1U << 1U);
    
    /* Initalize GPIOB as GPIO Digital Output */
    GPIOB_AHB->DIR |= BUTTON_LED;
    GPIOB_AHB->DEN |= BUTTON_LED;
    GPIOB_AHB->AMSEL &= ~BUTTON_LED;
    GPIOB_AHB->PCTL &= ~BUTTON_LED;
    GPIOB_AHB->AFSEL &= ~BUTTON_LED;
    
}

void toggleRedLED(void)
{
    GPIOF_AHB->DATA ^= LED_RED;
    GPIOF_AHB->DATA &= ~(LED_BLUE | LED_GREEN);
}


void toggleBlueLED(void)
{
    GPIOF_AHB->DATA ^= LED_BLUE;
    GPIOF_AHB->DATA &= ~(LED_RED | LED_GREEN);
}

void toggleGreenLED(void)
{
    GPIOF_AHB->DATA ^= LED_GREEN;
    GPIOF_AHB->DATA &= ~(LED_RED | LED_BLUE);
}

void toggleButtonLED(void)
{
    GPIOB_AHB->DATA ^= BUTTON_LED;
    
}

BaseType_t checkButton(void)
{
    return !(GPIOF_AHB->DATA & BUTTON_PIN);
    
}
