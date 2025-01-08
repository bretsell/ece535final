/**
 * @file hw01c.c
 * @author Prateek Tandon, Bret Sell
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw01.h"
#include "hw1_additional.h"

#if defined(HW01C)

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void memory_get_image(mem_image_t image, uint32_t *bitmap_addr, uint16_t *height, uint16_t *width);

// We moved most of the additional functions to hw1_additional.h and hw1_additional.c
// However, since the Handler needs to be static, it has to be in this file.
// Please see hw1_additional.c and hw1_additional.h
static void sw1Handler(void *handler_arg, cyhal_timer_event_t event);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW01C";

// MS_300 indicates we want to use the timer for 300 ms
bool MS_300;

// MS_1000 indicates we want to use the timer for 1s (1000ms)
bool MS_1000;

// Done is asserted once we have counted to that number of ms
bool done;

// Contains the actual address for the timer
cyhal_timer_t MS_10_timer;
cyhal_timer_cfg_t MS_10_timer_config;


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

    // This timer will count to 10 MS and will be used for 300ms and 1s time detection
    // 300ms is for the buzzer and 1s is for if the incorrect match was made
    timer_init(&MS_10_timer, &MS_10_timer_config, TICKS_MS_001 * 10, sw1Handler);
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
    // Holds the row and column value that we currently are at
    uint8_t row = 0;
    uint8_t col = 0;

    // Joystick position variables used to see if we have moved the joystick
    joystick_position_t pos_curr = JOYSTICK_POS_CENTER;
    joystick_position_t pos_prev = JOYSTICK_POS_CENTER;

    // This tracks the previous row/column combo that was selected.
    // {-1, -1} is when we have not selected a previous combo.
    // Order is {row, column}
    uint16_t prevCombo[2] = {-1, -1};

    // Defines the game board.
    // Please see hw1_additional.h for more information on Square.
    Square memory [4][4];

    // Will state when the game is finished
    bool finished = false;

    // Is asserted whenever the previous square was invalid (when the buzzer should play)
    // This is used so that we don't use the invalid square to compare in the matching game
    bool invalid = false;

    // Draws the 4-by-4 grid to the screen
    memory_draw_grid(true);

    /* Draw 353 In the Text Area of the board */
    memory_print_number(3, (LOC_X_CENTER - 15), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    memory_print_number(5, (LOC_X_CENTER - 0), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    memory_print_number(3, (LOC_X_CENTER + 15), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);

	
	// Draw 16 Question Marks to the screen
    // See hw1_additional.c for the implementation
	draw_question_marks(row, col);

    // Initializes all of the memory units to their color and image, and declares them hidden
    initialize_memory(memory);

    while (1)
    {
        // See if the joystick check timer is up
        // TIME_UP is defined in io-sw.c

        // !finished is there so that when we draw the game over screen,
        // additional joystick movements do not affect the game board.
        if (TIME_UP && !finished) {

            /* Set previous position, get new position */
            pos_prev = pos_curr;
            pos_curr = joystick_get_pos();

            /* Check if joystick has moved its previous position */
            if (pos_curr != pos_prev)
            {
                // Record the previous square
                uint8_t prevRow = row;
                uint8_t prevCol = col;

                /* Handle joystick movement */
                switch (pos_curr)
                {
                case JOYSTICK_POS_DOWN:
                    row = (row == 3) ? 3 : row+1; // If row = 3, stay at row 3
                    break;
                case JOYSTICK_POS_UP:
                    row = (row == 0) ? 0 : row-1; // If row=0, stay at 0
                    break;
                case JOYSTICK_POS_RIGHT:
                    col = (col == 3) ? 3 : col+1; // If col=3, stay at 3
                    break;
                case JOYSTICK_POS_LEFT:
                    col = (col == 0) ? 0 : col-1; // If col=0, stay at 0
                    break;

                // This should only run if we hit the center
                default:
                    break;
                }

                // I had seen a lot of "glitching" where the program would quickly draw/redraw the image when I didn't move the stick.
                // To fix this, we check to see if this is an actual different position.
                // If it is not a new row or a new column, then this is the same as earlier, so don't erase/redraw the same image
                if (prevRow != row || prevCol != col) {

                    // If we are here, then the user has selected a square that is NOT what the previous square was.
                    // Thus we need to change the active square back to a normal square

                    // Start by erasing the image
                    memory_erase_image(prevRow, prevCol);

                    // Now check to see if the previous image was hidden.
                    // If it was, then we need to draw a question mark with normal colors
                    if (memory[prevRow][prevCol].hidden) memory_draw_image(prevRow, prevCol, MEM_IMAGE_QUESTION, LCD_COLOR_GREEN, LCD_COLOR_BLACK);

                    // If it was not, then we need to draw the image the square should be (club, heart, etc.) with normal colors
                    else memory_draw_image(prevRow, prevCol, memory[prevRow][prevCol].theImage, memory[prevRow][prevCol].highlightColor, LCD_COLOR_BLACK);
    
                    // Now we need to change the color of the new active square

                    // Erase previous image
                    memory_erase_image(row, col);

                    // If the new square is hidden, invert the question mark colors
                    if (memory[row][col].hidden) memory_draw_image(row, col, MEM_IMAGE_QUESTION, LCD_COLOR_BLACK, LCD_COLOR_GREEN);

                    // Otherwise, invert the color of the shape it should be
                    else memory_draw_image(row, col, memory[row][col].theImage, LCD_COLOR_BLACK, memory[row][col].highlightColor);

                }

                /* Wait for joystick to return to center */
                while (joystick_get_pos() != JOYSTICK_POS_CENTER)
                {
                }

                /* Set TIME_UP to false since we are done with this check */
                TIME_UP = false;
            }
        }

        /* Checks if Switch 1 is pressed. When pressed, we should either play the buzzer or reveal a shape.*/
        if (ALERT_SW1 == BUTTON_PRESSED)
        {
            // We also check to see if we are finished or not. If we are finished, then the game over screen is being shown.
            // Thus at this point pressing SW1 should do nothing, so even if we are alerted we will just declare
            // If the current square is "hidden", then the user made a valid input.
            // Thus we should draw the correct image with inverted colors (since the square was selected)
            if (!finished) {
                if (memory[row][col].hidden) {
                    memory_erase_image(row, col);
                    memory_draw_image(row, col, memory[row][col].theImage, LCD_COLOR_BLACK, memory[row][col].highlightColor);
                    memory[row][col].hidden = false;
                }

                // If it was NOT hidden, then the user picked an already active square.
                // This means we need to assert the buzzer for 300ms
                else {
                    MS_300 = true;
                    pwm_buzzer_start();
                
                    // Buzzer is playing here

                    // The timer will assert done when it has been 300ms
                    // Until then we wait
                    while (!done) {}

                    // Deassert done and MS_300 (we are done with the timer), and stop the buzzer
                    done = false;
                    MS_300 = false;
                    pwm_buzzer_stop();

                    // Ensure that we don't use this row/col combination to check if it is matching
                    // Thus we set invalid to true and only compare if invalid is still false
                    invalid = true;
                }
                if (!invalid) {

                    // This is an array purely used to see if prevCombo is still at {-1, -1}
                    // We declare it here and then use memcmp to see if the arrays are equal
                    int nullArray[2] = {-1, -1};
                    if (memcmp(prevCombo, nullArray, 2)) {
                        // Array is NOT {-1, -1}
                        // That means prevCombo is storing a row/col combination!
                        // So this was the second image selected, so see if it matches the previous image
                        if (memory[prevCombo[0]][prevCombo[1]].theImage == memory[row][col].theImage) {
                            // If we are here, they matched! Thus they were "found"
                            memory[prevCombo[0]][prevCombo[1]].found = true;
                            memory[row][col].found = true;

                            // Please see hw1_additional.c for the implementation of checkVictory.
                            // It simply returns true if all squares have been "found"
                            if (checkVictory(memory)) {

                                // If we are here, the game is over! So display the game over screen
                                lcd_draw_image(LOC_X_GAME_BOARD_CENTER, LOC_Y_GAME_BOARD_CENTER, 
                                    IMAGE_GAME_OVER_PIXEL_WIDTH, IMAGE_GAME_OVER_PIXEL_HEIGHT, 
                                    IMAGE_GAME_OVER, LCD_COLOR_BLUE, LCD_COLOR_BLACK);

                                // Ensure no joystick movements or SW1 presses do anything since the game is over
                                finished = true;
                            }
                        }

                        // (this else statement is from memory[prev].image == memory[current].image)
                        else {
                            // If we are here, then the two images didn't match
                            // That means we need to start a timer for 1s (1000ms) and then hide both images
                            MS_1000 = true;

                            // We wait until the timer tells us we are done.
                            while (!done) {}

                            // Deassert these two variables so we can use them correctly for another timer
                            done = false;
                            MS_1000 = false;

                            // Now we need to erase the two images and replace both of them with question marks.
                            // The current square has its colors inverted because it is still the active square.
                            memory_erase_image(row, col);
                            memory_erase_image(prevCombo[0], prevCombo[1]);
                            memory_draw_image(row, col, MEM_IMAGE_QUESTION, LCD_COLOR_BLACK, LCD_COLOR_GREEN);
                            memory_draw_image(prevCombo[0], prevCombo[1], MEM_IMAGE_QUESTION, LCD_COLOR_GREEN, LCD_COLOR_BLACK);

                            // The two images are now hidden, set their variable accordingly
                            memory[row][col].hidden = true;
                            memory[prevCombo[0]][prevCombo[1]].hidden = true;
                        }

                        // No matter if the previous combo was a match or not, we have resolved what we needed with the previous square.
                        // Thus we set them back to {-1, -1} so our program knows another SW1 press is the first square being selected
                        // for comparisons.
                        prevCombo[0] = -1;
                        prevCombo[1] = -1;
                    }

                    // (This else statement is from memcmp({-1, -1}, prevCombo))
                    else {
                        // If we are here, then prevCombo IS {-1, -1}
                        // Thus this was the first square selected
                        // Record this in prevCombo
                        prevCombo[0] = row;
                        prevCombo[1] = col;
                    }
                }
            }
            /*Button is set back to inactive to detect falling edge */
            ALERT_SW1 = BUTTON_INACTIVE;

            // We are done with this switch interaction, so deassert invalid
            // if it previously was true
            invalid = false;
        }

        /* Checks if Switch 2 is pressed. When pressed, the game should reset. */
        if (ALERT_SW2 == BUTTON_PRESSED)
        {
            if (finished) {

                // Clear everything and redraw the 353 / grid
                lcd_clear_screen(LCD_COLOR_BLACK);

                /* Draw 353 In the Text Area of the board */
                memory_print_number(3, (LOC_X_CENTER - 15), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                memory_print_number(5, (LOC_X_CENTER - 0), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                memory_print_number(3, (LOC_X_CENTER + 15), LOC_Y_TIME, LCD_COLOR_GREEN, LCD_COLOR_BLACK);

                memory_draw_grid(true);

                // Redraw the question marks
                draw_question_marks(row, col);

                // Re-initialize memory
                // This also changes hidden and found back to false for every square
                initialize_memory(memory);

                // Even if there was a previous row/column selected, we are restarting, so reset back to default
                // prevCombo should already be -1 since there are an even number of squares, so we just finished.
                // However just in case we specifically reset them here.
                prevCombo[0] = -1;
                prevCombo[1] = -1;

                // We are no longer finished, it's a new game
                finished = false;
            }

            /* Button is set back to inactive to detect falling edge */
            ALERT_SW2 = BUTTON_INACTIVE;
        }

    }
}


// Handler
// Timer logic for 300ms timer and 1000ms timer
static void sw1Handler(void *handler_arg, cyhal_timer_event_t event)
{
    // Our timer counts for 10ms.
    // These variables help us count the number of times we have triggered the handler
    static uint8_t counter300 = 0;
    static uint8_t counter1000 = 0;

    // Only increment counter300 if we had asserted MS_300
    // (if we asserted MS_300, we want to count to 300ms)
    if (MS_300) {
        // Cut off counter so it doesn't overflow
        counter300 = (counter300 >= 40) ? 40 : counter300 + 1;

        // If we hit counter300 = 30, then 30 * 10ms = 300ms have passed.
        if (counter300 == 30) done = true;
    }

    // Otherwise keep the counter at 0
    else counter300 = 0;


    // Similar logic for counting to 1000ms
    if (MS_1000) {
        // Cap counter so it won't overflow
        counter1000 = (counter1000 >= 110) ? 110 : counter1000 + 1;

        // 100 * 10ms = 1s = 1000ms
        if (counter1000 == 100) done = true;
    }
    else counter1000 = 0;
}
#endif
