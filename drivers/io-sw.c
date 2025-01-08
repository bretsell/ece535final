/**
 * @file io-sw.c
 * @author Prateek Tandon, Bret Sell
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "io-sw.h"

/*****************************************************************************/
/* Public Global Variables */
/*****************************************************************************/
button_state_t ALERT_SW1 = BUTTON_INACTIVE;
button_state_t ALERT_SW2 = BUTTON_INACTIVE;
button_state_t ALERT_SW3 = BUTTON_INACTIVE;

// This is used for the joystick timer.
bool TIME_UP = false;

/*****************************************************************************/
/* Static Function Declarations */
/*****************************************************************************/
static void Handler_Timer_Buttons(void *handler_arg, cyhal_timer_event_t event);
static void push_buttons_timer_init(void);

/*****************************************************************************/
/* ICE 02 START */
/*****************************************************************************/
void push_buttons_init(bool enable_timer_irq)
{
    /* ADD CODE */
    /* Initialize the IO Pins connected to the push buttons as inputs */
    cy_rslt_t rslt_s1 = cyhal_gpio_init(PIN_SW1, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    CY_ASSERT(rslt_s1 == CY_RSLT_SUCCESS);
    cy_rslt_t rslt_s2 = cyhal_gpio_init(PIN_SW2, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    CY_ASSERT(rslt_s2 == CY_RSLT_SUCCESS);
    cy_rslt_t rslt_s3 = cyhal_gpio_init(PIN_SW3, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    CY_ASSERT(rslt_s3 == CY_RSLT_SUCCESS);
    /* ADD CODE */
    if(enable_timer_irq)
    {
        push_buttons_timer_init();
    }
} 
/*****************************************************************************/
/* ICE 02 END */
/*****************************************************************************/

/*****************************************************************************/
/* ICE 06 START */
/*****************************************************************************/

/*
 * Handler used to debounce the push buttons
*/
static void Handler_Timer_Buttons(void *handler_arg, cyhal_timer_event_t event)
{

    // The timer is up so set that to true so we can look for it in hw01b.c
    TIME_UP = true;

    /* Static Vars */

    uint32_t reg_val = PORT_BUTTONS->IN;
    static uint32_t oneCnt = 0;
    static uint32_t twoCnt = 0;
    static uint32_t threeCnt = 0;

    /* Many mechanical buttons will bounce when they are pressed.
    *  The signal may oscillate between 0 and 1 for several milliseconds.
    *
    * We will debounce a button by sampling the button and detecting the first
    * 50mS interval of time when the button is low.  When that period of time is
    * detected, we will alert the main application using ALERT_SW1, ALERT_SW2, 
    * and ALERT_SW3.
    */

    // Detect falling edge of the button being pressed
    if (!(reg_val & SW1_MASK)) {
        oneCnt = oneCnt + 1; 
        if (oneCnt > 10) oneCnt = 10; // Keep at 10 so that it doesn't keep looping
        
        // Only at 50ms will we make the button pressed
        if (oneCnt == 5) {            
            ALERT_SW1 = BUTTON_PRESSED;
        }
    }
    else {
        oneCnt = 0;
    }

    // Detect falling edge of the button being pressed
    if (!(reg_val & SW2_MASK)) {
        twoCnt = (twoCnt > 10) ? 10 : twoCnt + 1; // Keep at 10 for same reasons as above

        // 50ms button press
        if (twoCnt == 5) ALERT_SW2 = BUTTON_PRESSED;
    }
    else {
        twoCnt = 0;
    }

    // Detect falling edge of the button being pressed
    if (!(reg_val & SW3_MASK)) {
        threeCnt = (threeCnt > 10) ? 10 : threeCnt + 1; // Prevent overflow

        // 50ms button press
        if (threeCnt == 5) ALERT_SW3 = BUTTON_PRESSED;
    }
    else {
        threeCnt = 0;
    }

   /* ADD CODE */

}

/* ADD CODE */
/* Allocate static variables for a cyhal_timer_t and cyhal_timer_cfg_t that will be used
 * to configure the button timer*/
static cyhal_timer_t timer_obj;
static cyhal_timer_cfg_t timer_cfg;

static void push_buttons_timer_init(void)
{
    /*ADD CODE*/
    /*
     * Use timer_init() to configure a timer that generates an interrupt every 10mS
     * This timer will be used to debounce the push buttons  on the ECE353 Dev Board
     */
    timer_init(&timer_obj, &timer_cfg, 1000000, Handler_Timer_Buttons);
}
/*****************************************************************************/
/* ICE 06 END */
/*****************************************************************************/
