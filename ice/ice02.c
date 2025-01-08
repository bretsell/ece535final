/**
 * @file ice02.c
 * @author Bret Sell brsell@wisc.edu
 * @brief
 * @version 0.1
 * @date 2024-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE02)

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: ICE 02 - Memory Mapped IO";

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    push_buttons_init(false);
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    bool sw1_pressed = false;
    bool sw2_pressed = false;
    bool sw3_pressed = false;
    uint32_t detectIO;

    while (1)
    {
        /* ADD CODE */
        /* Read the IO Port that is connected to the buttons */
        detectIO = REG_PUSH_BUTTON_IN;

        /* ADD CODE */
        /* if the SW1 is pressed, set sw1_pressed to true.*/       
        /* if the SW1 is NOT pressed, set sw1_pressed to false.*/       
       sw1_pressed = !(detectIO & SW1_MASK);

        /* ADD CODE */
        /* if the SW2 is pressed, set sw2_pressed to true.*/       
        /* if the SW2 is NOT pressed, set sw2_pressed to false.*/   
        sw2_pressed = !(detectIO & SW2_MASK);    
        
        /* ADD CODE */
        /* if the SW3 is pressed, set sw3_pressed to true.*/       
        /* if the SW3 is NOT pressed, set sw3_pressed to false.*/   
        sw3_pressed = !(detectIO & SW3_MASK);

        if (sw1_pressed)
        {
            printf("SW1 is pressed\n\r");
        }

        if (sw2_pressed)
        {
            printf("SW2 is pressed\n\r");
        }

        if (sw3_pressed)
        {
            printf("SW3 is pressed\n\r");
        }

        /* Delay 100mS before checking the buttons again*/
        cyhal_system_delay_ms(100);
    }
}
#endif