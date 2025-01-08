/**
 * @file hw01a.c
 * @author Prateek Tandon, Bret Sell
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw01.h"

#if defined(HW01A)



/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW01A";


/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{

    ece353_enable_lcd();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void main_app(void)
{
    // Initialize all of the variables we will be using to the initial image values
    uint8_t x = 0;
    uint8_t y = 0;
    uint16_t color = LCD_COLOR_BLUE;
    mem_image_t image = MEM_IMAGE_CLUB;

    // incrementor helps keep track of what square we need to be printing next
    uint8_t incrementor = 0;

    // overallIncrementor helps keep track of what the current shape/color is,
    // helping change to the correct color/image in the pattern.
    uint8_t overallIncrementor = 0;

    memory_draw_grid(true);

    /* Draw Initial Image*/
    memory_draw_image(x, y, image, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
    cyhal_system_delay_ms(200);

    
    while (1)
    {
        /* ADD CODE*/
        /* Write the code that will display the images as described in the HW01A 
         * document
         */

        // We start by erasing the current image.
        // This is because we drew the initial image outside of the loop
        // We start each loop by erasing the image and end each loop by drawing a new image
        memory_erase_image(x, y);

        // incrementor is used to determine what x/y position to go to next.
        // if incrementor is 0, 4, 8, or 12, we want to have x=0
        // if incrementor is 1, 5, 9, or 13, we want to have x=1. etc.
        // This exactly matches up with what how the modulus operator works.
        // Thus to efficiently find the x value we take incrementor mod 4.
        x = incrementor % 4;

        // if incrementor is 0, 1, 2, or 3, we want y = 0.
        // if incrementor is 4, 5, 6, or 7, we want y = 1. etc.
        // This matches how integer division works in C. 
        // In C, an integer divided by an integer equals an integer.
        // Thus 0/4 = 1/4 = 2/4 = 3/4 = 0 in C.
        // Similarly 4/4 =5/4 = 6/4 = 7/4 = 1 in C.
        // This matches up with what we want y to be, so we use this operation
        y = incrementor / 4;

        // Background color will always be black
        memory_draw_image(x, y, image, color, LCD_COLOR_BLACK);
        incrementor++;

        if (incrementor == 16) {
            // If we made it here, we reached the bottom right corner of the screen.
            // Thus we need to go back to 0 and change the shape/color of the image

            // When overallIncrementor is 4, we need to set it back to 0.
            // The modulus operation allows us to efficiently do this.
            overallIncrementor = (overallIncrementor + 1) % 4;

            // If Incrementor was previously 0 (Club) or 2 (Heart),
            // We want to change the color from blue to red.
            // If it was previously 1 (spade) or 3 (diamond), we want to go from red to blue.
            // Taking modulus 2 allows us to tell whether overallIncrementor is even or odd.
            // If it is even, we know the previous value was odd, so we go to blue.
            // If it is not, then the previous value was even so we go to red.
            color = (overallIncrementor % 2 == 0) ? LCD_COLOR_BLUE : LCD_COLOR_RED;

            // Set the next image
            switch (overallIncrementor) {
                case 0: image = MEM_IMAGE_CLUB; break;
                case 1: image = MEM_IMAGE_SPADE; break;
                case 2: image = MEM_IMAGE_HEART; break;
                case 3: image = MEM_IMAGE_DIAMOND; break;

                // That is all of the possible images. For safety if incrementor is none of these,
                // we just make the image a question mark
                default: image = MEM_IMAGE_QUESTION; break;
            }

            // Reset incrementor so we go back to the top left corner
            incrementor = 0;
        }

        cyhal_system_delay_ms(200);
    }

}

#endif