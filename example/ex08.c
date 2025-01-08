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

#if defined(EX08)

#define TICKS_MS_100 10000000

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/
typedef enum {
    ALERT_TIMER_NONE,
    ALERT_TIMER_100MS
}alert_timer_t;

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: Ex08 - ADC";

/* Timer object and timer_cfg object */
cyhal_timer_t timer_obj;
cyhal_timer_cfg_t timer_cfg;

alert_timer_t ALERT_TIMER = ALERT_TIMER_NONE;

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_Timer(void *handler_arg, cyhal_timer_event_t event)
{
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
    /* Initialize a timer */
    timer_init(&timer_obj, &timer_cfg, TICKS_MS_100, Handler_Timer);

    /* Initialize the Joystick */
    joystick_init();
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
