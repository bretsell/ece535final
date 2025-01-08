/**
 * @file ice04.c
 * @author Bret Sell brsell@wisc.edu
 * @brief
 * @version 0.1
 * @date 2024-02-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE04)

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: ICE 04 - LCD";

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
    /* Initialize the LCD Screen */
    ece353_enable_lcd();
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    // Turn LCD On
    lcd_draw_image(
        160,
        120,
        wisconsinWidthPixels,
        wisconsinHeightPixels,
        wisconsinBitmaps,
        LCD_COLOR_RED,
        LCD_COLOR_BLACK);

    for (;;)
    {
    }
}
#endif