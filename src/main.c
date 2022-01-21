#include "main.h"

int main() {

    HAL_Init();        

    SYSTEM_INIT();          // set system clock

    hal_uart_init();        // init uart 

    printf_info();          // print debug info
    
    HAL_Delay(500);

    while(1){

    };
}


/*
 * Author:sola
 * Fix time:2022-01-20
 * Describe:
 * This is for the tick of the HAL library, using Systick's interrupt 
 * to perform the count
*/
void SysTick_Handler(void)
{
    HAL_IncTick();
}