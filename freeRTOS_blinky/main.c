#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "bsp.h"

#define DEBOUNCE_TIME 50


static void vBlinkyBlue(void *pvParameters);
static void vCheckButton(void *pvParameters);

int main(void) 
{
    PortF_Init();
    ButtonLEDInit();
    
    xTaskCreate(vBlinkyBlue, (const portCHAR*)"BlinkyBlue", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vCheckButton, (const portCHAR*)"vCheckButton", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  
    /* Start the scheduler */
    vTaskStartScheduler();
    
}

static void vBlinkyBlue(void *pvParameters)
{
    (void) pvParameters;
    while (1) 
    {
        taskENTER_CRITICAL();
        toggleBlueLED();
        taskEXIT_CRITICAL();
        vTaskDelay(pdMS_TO_TICKS(500));
        
    }
    
}

static void vCheckButton(void *pvParameters)
{
    TimeOut_t xTimeOut;
    BaseType_t xTimeOutState = pdFALSE;
    BaseType_t xLastKey = 0;
    TickType_t xDebounceTime;
    
    (void) pvParameters;
    
    while (1) 
    {
        BaseType_t xKeyPressed = checkButton();
        
        /* When state change and not in timeout, handle new key status */
        if (xTimeOutState == pdFALSE && xLastKey != xKeyPressed) {
            /* If new state is HIGH, handle button press */
            if (xKeyPressed == pdTRUE) {
                taskENTER_CRITICAL();
                toggleButtonLED();
                taskEXIT_CRITICAL();
            }
            xLastKey = xKeyPressed;
            xDebounceTime = DEBOUNCE_TIME;
            vTaskSetTimeOutState(&xTimeOut);
            xTimeOutState = pdTRUE;
        }
        
        /* Check timeout status if waiting */
        if (xTimeOutState == pdTRUE) {
            if (xTaskCheckForTimeOut(&xTimeOut, &xDebounceTime)) {
                xTimeOutState = pdFALSE;
            }
        }
    }
    
}



