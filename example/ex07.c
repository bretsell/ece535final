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

#if defined(EX07)

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: Ex07 - Timer Interrupts, PWM";

cyhal_timer_cfg_t timer_led_cfg;
cyhal_timer_t timer_led_obj;

cyhal_pwm_t pwm_ex_blue_obj;

#define DUTY_CYCLE 88 

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_Timer_LED(void *handler_arg, cyhal_timer_event_t event)
{
    static uint8_t pwm_count = 0;

    pwm_count = (pwm_count + 1) % 100;

    if(pwm_count == 0)
    {
        PORT_RGB_BLU->OUT_SET = MASK_RGB_BLU;
    }
    else if(pwm_count == DUTY_CYCLE)
    {
        PORT_RGB_BLU->OUT_CLR = MASK_RGB_BLU;
    }
}

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
    cy_rslt_t rslt;
#if 0
    /* Initialize leds */
    leds_init();
    timer_init(&timer_led_obj, &timer_led_cfg, 10000, Handler_Timer_LED);
#else
    /* Configure the IO pin connected to the BLUE LED as a PWM pin */
    rslt = cyhal_pwm_init(&pwm_ex_blue_obj, PIN_RGB_BLU, NULL);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    /* Set the Duty Cycle */
    cyhal_pwm_set_duty_cycle(&pwm_ex_blue_obj, DUTY_CYCLE, 100);

    /* Start the PWM peripheral */
    cyhal_pwm_start(&pwm_ex_blue_obj);

#endif
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
    /* Enter Infinite Loop*/
    while (1)
    {
    }
}
#endif