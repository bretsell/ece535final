/**
 * @file hw01a.c
 * @author Prateek Tandon, Bret Sell
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw01.h"

#if defined(HW01B)

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void memory_get_image(mem_image_t image, uint32_t *bitmap_addr, uint16_t *height, uint16_t *width);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW01B";

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

    joystick_init();

    push_buttons_init(true);

    pwm_buzzer_init();
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
    uint8_t row = 0;
    uint8_t col = 0;
    uint8_t image = 0;
    uint16_t color = LCD_COLOR_BLUE;
    joystick_position_t pos_curr = JOYSTICK_POS_CENTER;
    joystick_position_t pos_prev = JOYSTICK_POS_CENTER;
    bool buzzer_on = false;

    memory_draw_grid(true);

    /* Draw 353 In the Text Area of the board */
    memory_print_number(3, (LOC_X_CENTER - 15), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    memory_print_number(5, (LOC_X_CENTER - 0), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    memory_print_number(3, (LOC_X_CENTER + 15), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);

    /* Draw Initial Image*/
    memory_draw_image(row, col, (mem_image_t)image, color, LCD_COLOR_BLACK);

    while (1)
    {
        // See if the timer is up
        // TIME_UP is defined in io-sw.c
        // This is so that we use the same timer for the stick and buttons
        // (rather than having two different timers going)

        if (TIME_UP) {

            /* Set previous position, get new position */
            pos_prev = pos_curr;
            pos_curr = joystick_get_pos();

            /* Check if joystick has moved its previous position */
            if (pos_curr != pos_prev)
            {
                /* Handle joystick movement */
                switch (pos_curr)
                {
                case JOYSTICK_POS_DOWN:
                    if (row < 3)
                    { // Check boundary
                        memory_erase_image(row, col);
                        row++;
                    }
                    break;
                case JOYSTICK_POS_UP:
                    if (row > 0)
                    { // Check boundary
                        memory_erase_image(row, col);
                        row--;
                    }
                    break;
                case JOYSTICK_POS_RIGHT:
                    if (col < 3)
                    { // Check boundary
                        memory_erase_image(row, col);
                        col++;
                    }
                    break;
                case JOYSTICK_POS_LEFT:
                    if (col > 0)
                    { // Check boundary
                        memory_erase_image(row, col);
                        col--;
                    }
                    break;
                default:
                    break;
                }

                /* Redraw image at new position */
                memory_draw_image(row, col, (mem_image_t)image, color, LCD_COLOR_BLACK);

                /* Wait for joystick to return to center */
                while (joystick_get_pos() != JOYSTICK_POS_CENTER)
                {
                }

                /* Set TIME_UP to false since we are done with this check */
                TIME_UP = false;
            }
        }

        /* Checks if Switch 1 is pressed. When pressed, the image will change between club, spade, heart, diamond, question.
         Image is first erased then new image is drawn in.*/
        if (ALERT_SW1 == BUTTON_PRESSED)
        {
            memory_erase_image(row, col);
            image = (image + 1) % 5;
            memory_draw_image(row, col, (mem_image_t)image, color, LCD_COLOR_BLACK);
            /*Button is set back to inactive to detect falling edge */
            ALERT_SW1 = BUTTON_INACTIVE;
        }

        /* Checks if Switch 2 is pressed. When pressed, the image color is changed to either blue or red. Image is first 
            erased then image with new color is drawn in. */
        if (ALERT_SW2 == BUTTON_PRESSED)
        {
            memory_erase_image(row, col);
            color = (color == LCD_COLOR_BLUE) ? LCD_COLOR_RED : LCD_COLOR_BLUE;
            memory_draw_image(row, col, (mem_image_t)image, color, LCD_COLOR_BLACK);
            /* Button is set back to inactive to detect falling edge */
            ALERT_SW2 = BUTTON_INACTIVE;
        }

        /* Checks if Switch 3 is pressed. When pressed, the buzzer is toggled on or off. */
        if (ALERT_SW3 == BUTTON_PRESSED)
        {
            if (!buzzer_on)
                pwm_buzzer_start();
            else
                pwm_buzzer_stop();
            buzzer_on = !buzzer_on;
            /* Button is set back to inactive to detect falling edge */
            ALERT_SW3 = BUTTON_INACTIVE;
        }
    }
}

#endif