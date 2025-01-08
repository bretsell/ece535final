/**
 * @file ice07.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE06)

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: ICE06 - PWM";

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    /* This function needs to be written as part of the Ex07 PWM video*/
    leds_pwm_init();
}
/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
static void ice06_update_duty_cycle(cyhal_pwm_t *pwm_obj, uint8_t duty_cycle)
{
    cy_rslt_t rslt = CY_RSLT_SUCCESS;

    /* Stop the PWM generation */
    /* ADD CODE */

    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization, halt the MCU

    /* Change the Duty Cycle */
    /* ADD CODE */

    /* Start the PWM generation */
    /* ADD CODE */

    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization, halt the MCU
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    uint8_t red_duty_cycle = 0;
    uint8_t green_duty_cycle = 0;
    uint8_t blue_duty_cycle = 0;

    while (1)
    {
        while(red_duty_cycle <= 100)
        {
            /* ADD CODE Set the duty cycle for the red LED */
            
            printf("Red %02d, Green %02d, Blue %02d\n\r", red_duty_cycle, green_duty_cycle, blue_duty_cycle);

            cyhal_system_delay_ms(200);

            /* ADD CODE increment the red duty cycle by 10 */
        }

        /*ADD CODE Turn off the red LED */

        while(green_duty_cycle <= 100)
        {
            /* ADD CODE Set the duty cycle for the green LED */
            
            printf("Red %02d, Green %02d, Blue %02d\n\r", red_duty_cycle, green_duty_cycle, blue_duty_cycle);

            cyhal_system_delay_ms(200);

            /* ADD CODE increment the green duty cycle by 10 */
        }

        /*ADD CODE Turn off the green LED */

        while(blue_duty_cycle <= 100)
        {
            /* ADD CODE Set the duty cycle for the blue LED */
            
            printf("Red %02d, Green %02d, Blue %02d\n\r", red_duty_cycle, green_duty_cycle, blue_duty_cycle);

            cyhal_system_delay_ms(200);

            /* ADD CODE increment the blue duty cycle by 10 */
        }

        /*ADD CODE Turn off the blue LED */

    }
}

#endif