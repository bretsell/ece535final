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

#if defined(ICE07)

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: ICE07 - Timer Interrupts";


/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    /* Initialize the push buttons and turn on a timer to debounce the 
     * pushbuttons
     */
    push_buttons_init(true);

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
        /* ADD CODE */

        /* Print if SW1 has been pressed. */
        
        /* Print if SW2 has been pressed. */
        
        /* Print if SW3 has been pressed. */

    }   
}
#endif