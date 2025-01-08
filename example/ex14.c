/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX14)

char APP_DESCRIPTION[] = "ECE353: Example 14 - Temp Sensor";

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    i2c_init();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    float temp;

    while(1)
    {
        temp = LM75_get_temp();
        printf("Temp %.02f\n\r",temp);        
        cyhal_system_delay_ms(500);
    }
}
#endif
