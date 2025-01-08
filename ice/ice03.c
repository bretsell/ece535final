/**
 * @file ice03.c
 * @author Bret Sell brsell@wisc.edu
 * @brief
 * @version 0.1
 * @date 2024-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE03)

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: ICE 03 - PSoC6 IO Ports";

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
    cy_rslt_t rsltRed = cyhal_gpio_init(PIN_RGB_RED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
    cy_rslt_t rsltGrn = cyhal_gpio_init(PIN_RGB_GRN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
    cy_rslt_t rsltBlu = cyhal_gpio_init(PIN_RGB_BLU, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
    push_buttons_init(false);
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    button_state_t sw1_curr_state = BUTTON_INACTIVE;
    button_state_t sw1_prev_state = BUTTON_INACTIVE;
    
    button_state_t sw2_curr_state = BUTTON_INACTIVE;
    button_state_t sw2_prev_state = BUTTON_INACTIVE;
   
    button_state_t sw3_curr_state = BUTTON_INACTIVE;
    button_state_t sw3_prev_state = BUTTON_INACTIVE;

    uint32_t button_value = 0;

     for (;;)
    {
        /* Read in the current state of the pushbuttons into button_value */
        button_value = REG_PUSH_BUTTON_IN;

        /* If SW1 is being pressed, set sw1_curr_state to BUTTON_PRESSED */
        if(!(button_value & SW1_MASK))
        {
            sw1_curr_state = BUTTON_PRESSED;
        } else{
            sw1_curr_state = BUTTON_INACTIVE;
        }

        /* If SW2 is being pressed, set sw1_curr_state to BUTTON_PRESSED */
        if(!(button_value & SW2_MASK))
        {
            sw2_curr_state = BUTTON_PRESSED;
        } else{
            sw2_curr_state = BUTTON_INACTIVE;
        }
        /* If SW3 is being pressed, set sw1_curr_state to BUTTON_PRESSED */
        if(!(button_value & SW3_MASK))
        {
            sw3_curr_state = BUTTON_PRESSED;
        } else{
            sw3_curr_state = BUTTON_INACTIVE;
        }
        /* If the current state of SW1 is BUTTON_PRESSED and the previous state is BUTTON_INACTIVE 
         * turn the red LED on, else turn the red LED off.
         */
        if(sw1_curr_state == BUTTON_PRESSED && sw1_prev_state == BUTTON_INACTIVE){
            PORT_RGB_RED->OUT |= MASK_RGB_RED;
        } else {
            PORT_RGB_RED->OUT &= ~MASK_RGB_RED;
        }
        
        /* If the current state of SW2 is BUTTON_PRESSED and the previous state is BUTTON_INACTIVE 
         * turn the green LED on, else turn the green LED off.
         */
        if(sw2_curr_state == BUTTON_PRESSED && sw2_prev_state == BUTTON_INACTIVE){
            PORT_RGB_GRN->OUT |= MASK_RGB_GRN;
        } else {
            PORT_RGB_GRN->OUT &= ~MASK_RGB_GRN;
        }

        /* If the current state of SW3 is BUTTON_PRESSED and the previous state is BUTTON_INACTIVE 
         * turn the blue LED on, else turn the blue LED off.
         */
        if(sw3_curr_state == BUTTON_PRESSED && sw3_prev_state == BUTTON_INACTIVE){
            PORT_RGB_BLU->OUT |= MASK_RGB_BLU;
        } else {
            PORT_RGB_BLU->OUT &= ~MASK_RGB_BLU;
        }

        /* For each button, set local variable that holds the previous state to the current state of the button */
        sw1_prev_state = sw1_curr_state;
        sw2_prev_state = sw2_curr_state;
        sw3_prev_state = sw3_curr_state;


        /* Delay for 50 mS*/
        cyhal_system_delay_ms(50);
    }
}
#endif