#include "task_lcd.h"

#if defined(HW03A)

QueueHandle_t q_LCD;

/******************************************************************************
 * Static Variables
 *
 * These variables should never be accessed outside of this file
 ******************************************************************************/
static uint16_t VERTICAL_LUT[] = {LOC_Y_IMAGE_ROW0, LOC_Y_IMAGE_ROW1, LOC_Y_IMAGE_ROW2, LOC_Y_IMAGE_ROW3};
static uint16_t HORIZONTAL_LUT[] = {LOC_X_IMAGE_COL0, LOC_X_IMAGE_COL1, LOC_X_IMAGE_COL2, LOC_X_IMAGE_COL3};

/******************************************************************************
 * Static Functions
 *
 * These Functions should never be called outside of this file.
 ******************************************************************************/
static void staff_get_image(mem_image_t image, uint32_t *bitmap_addr, uint16_t *height, uint16_t *width)
{
    switch (image)
    {
    case MEM_IMAGE_CLUB:
    {
        *bitmap_addr = (uint32_t)IMAGE_CLUB;
        *height = IMAGE_CLUB_PIXEL_HEIGHT;
        *width = IMAGE_CLUB_PIXEL_WIDTH;
        break;
    }
    case MEM_IMAGE_SPADE:
    {
        *bitmap_addr = (uint32_t)IMAGE_SPADE;
        *height = IMAGE_SPADE_PIXEL_HEIGHT;
        *width = IMAGE_SPADE_PIXEL_WIDTH;
        break;
    }
    case MEM_IMAGE_HEART:
    {
        *bitmap_addr = (uint32_t)IMAGE_HEART;
        *height = IMAGE_HEART_PIXEL_HEIGHT;
        *width = IMAGE_HEART_PIXEL_WIDTH;
        break;
    }
    case MEM_IMAGE_DIAMOND:
    {
        *bitmap_addr = (uint32_t)IMAGE_DIAMOND;
        *height = IMAGE_DIAMOND_PIXEL_HEIGHT;
        *width = IMAGE_DIAMOND_PIXEL_WIDTH;
        break;
    }
    case MEM_IMAGE_QUESTION:
    {
        *bitmap_addr = (uint32_t)IMAGE_QUESTION;
        *height = IMAGE_QUESTION_PIXEL_HEIGHT;
        *width = IMAGE_QUESTION_PIXEL_WIDTH;
        break;
    }

    default:
    {
        while (1)
        {
        };
    }
    }
}

/**
 * @brief
 *  Draws the specified image at the coordinates specified by row and col
 * @param row
 *      Specifies which row the image is located in
 * @param col
 *      Specifies which column the image is located in
 * @param image
 *      Specifies which image to draw
 * @param fcolor
 *      Specifies the foreground color of the image
 * @param bcolor
 *      Specifies the background color of the image
 */
static void staff_draw_image(uint8_t row, uint8_t col, mem_image_t image, uint16_t fcolor, uint16_t bcolor)
{
    uint16_t x = 0;
    uint16_t y = 0;
    uint32_t bitmap_addr;
    uint16_t height;
    uint16_t width;

    if (row > 3)
    {
        return;
    }

    if (col > 3)
    {
        return;
    }

    x = HORIZONTAL_LUT[col];
    y = VERTICAL_LUT[row];

    /* Erase what is currently at the desired location */
    lcd_draw_rectangle_centered(x, y, WIDTH_IMAGE, HEIGHT_IMAGE, LCD_COLOR_BLACK);

    /* Draw the new image */
    staff_get_image(image, &bitmap_addr, &height, &width);

    lcd_draw_image(x, y, width, height, (const uint8_t *)bitmap_addr, fcolor, bcolor);
}

/**
 * @brief
 * Prints out the grid of the game board
 * @param print_debug
 * If set to true, print out additional debug information about the location of the borders to
 * the serial console
 */
static void staff_set_grid_color(uint16_t color)
{
    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW0,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW1,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW2,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW3,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW4,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        color);

    /* Draw the vertical lines on the screen */
    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL0,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL1,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL2,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL3,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        color);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL4,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        color);
}
/******************************************************************************
 * End of Static Functions
 ******************************************************************************/

/******************************************************************************
 * FreeRTOS Related Functions
 ******************************************************************************/

/**
 * @brief
 * The LCD Task is the only task that is allowed to directly interface with the LCD.
 * Any task that wants to update what is currently being displayed on the LCD MUST
 * send a message to q_LCD.
 *
 * The LCD Task will wake up when data is received from q_LCD.
 * q_LCD allows other tasks to send Square_t data structures which
 * contain information related to what images/grid/etc need to be drawn on the
 * screen.
 *
 * The LCD Task will determine what type of operation is being requested by looking at the
 * image_type field of the Square_t data structure it receives.
 *
 * When drawing images, you will need to determine if the image is hidden.  If the Image is hidden,
 * draw the Question Mark Image.
 *
 * When drawing images, you will need to determine if the image is active.  If the Image is active,
 * invert the foreground and background colors.
 *
 * @param param
 */
void task_lcd(void *param)
{
    Square_t square;
    /* Suppress warning for unused parameter */
    (void)param;

    /* Draw the Initial Grid */
    staff_set_grid_color(LCD_COLOR_ORANGE);

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* Wait for data received from q_LCD */
        xQueueReceive(q_LCD, &square, portMAX_DELAY);

        // Determine the operation requested based on image_type field
        // Set grid color to orange for active grid
        if (square.image_type == MEM_IMAGE_GRID_ACTIVE) staff_set_grid_color(LCD_COLOR_ORANGE);
        // Set grid color to gray for inactive grid
        else if (square.image_type == MEM_IMAGE_GRID_INACTIVE) staff_set_grid_color(LCD_COLOR_GRAY);
        // Clear the screen for reset
        else if (square.image_type == MEM_IMAGE_LCD_RESET) lcd_clear_screen(LCD_COLOR_BLACK);
        // Draw game over image when game is complete
        else if (square.image_type == MEM_IMAGE_GAME_OVER) lcd_draw_image(LOC_X_GAME_BOARD_CENTER, LOC_Y_GAME_BOARD_CENTER, 
                                    IMAGE_GAME_OVER_PIXEL_WIDTH, IMAGE_GAME_OVER_PIXEL_HEIGHT, 
                                    IMAGE_GAME_OVER, LCD_COLOR_GRAY, LCD_COLOR_BLACK);
        else {
            // Determine if the image is hidden
            if (square.active) {
                if (square.status == SQUARE_STATUS_NOT_SELECTED) {
                    // Draw question mark image if not selected and active
                    staff_draw_image(square.row, square.col, MEM_IMAGE_QUESTION, LCD_COLOR_BLACK, LCD_COLOR_GREEN);
                }

                // Draw image with inverted colors if selected and active
                else {
                    staff_draw_image(square.row, square.col, square.image_type, square.bcolor, square.fcolor);
                }
            }

            else {
                if (square.status == SQUARE_STATUS_NOT_SELECTED) {
                    // Draw question mark image if not selected and inactive
                    staff_draw_image(square.row, square.col, MEM_IMAGE_QUESTION, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                }
                else {
                    // Draw image with normal colors if selected and inactive
                    staff_draw_image(square.row, square.col, square.image_type, square.fcolor, square.bcolor);
                }
            }
        }

        /*Be sure to use the staff_draw_image and staff_set_grid_color (found above)
         * to draw images and the grid lines */
    }
}

void task_lcd_init(void)
{

    /* Initialize the LCD hardware */
    ece353_enable_lcd();

    /* Create LCD Queues */
    q_LCD = xQueueCreate(1, sizeof(Square_t));

    xTaskCreate(
        task_lcd,
        "Task_LCD",
        10 * configMINIMAL_STACK_SIZE,
        NULL,
        HW03_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif