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

#if defined(ICE08)

#define TICKS_MS_100 (10000000)

typedef enum {
    ALERT_TIMER_NONE,
    ALERT_TIMER_100MS
}alert_timer_t;

char APP_DESCRIPTION[] = "ECE353: ICE 08 - ADC";

/*****************************************************************************/
/*  Function Declaration                                                     */
/*****************************************************************************/
void Handler_Timer(void *handler_arg, cyhal_timer_event_t event);

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
volatile alert_timer_t ALERT_TIMER = ALERT_TIMER_NONE; 

/* Timer object used */
cyhal_timer_t timer_obj;
cyhal_timer_cfg_t timer_cfg;

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_Timer(void *handler_arg, cyhal_timer_event_t event)
{
    /* ADD CODE*/
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
    /* ADD CODE */

    /* Initialize a timer to generate an interrupt every 100mS*/

    /* Initialize the X and Y directions of the joystick to be ADC pins*/

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
    joystick_position_t curr_position = JOYSTICK_POS_CENTER;
    joystick_position_t prev_position = JOYSTICK_POS_CENTER;

    while (1)
    {
        if (ALERT_TIMER == ALERT_TIMER_100MS)
        {
            /* Set Interrupt flag back to false*/
            ALERT_TIMER = ALERT_TIMER_100MS;

            /* Save the previous position */
            prev_position = curr_position;

            /* Get the current position */
            curr_position = joystick_get_pos();

            /* If the joystick was moved, print its new position*/
            if (curr_position != prev_position)
            {
                printf("Joystick now in ");
                joystick_print_pos(curr_position);
                printf(" position\n\r");
            }
        }
    }
}
#endif