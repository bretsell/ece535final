/**
 * @file memory.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "memory.h"

#if defined(HW02A)

extern cyhal_trng_t trng_obj;

uint16_t VERTICAL_LUT[] = {LOC_Y_IMAGE_ROW0, LOC_Y_IMAGE_ROW1, LOC_Y_IMAGE_ROW2, LOC_Y_IMAGE_ROW3};
uint16_t HORIZONTAL_LUT[] = {LOC_X_IMAGE_COL0, LOC_X_IMAGE_COL1, LOC_X_IMAGE_COL2, LOC_X_IMAGE_COL3};


/******************************************************************************
 * Static Functions 
 * 
 * These Functions should never be called outside of memory_staff.c
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
 * Swaps two Image_Location structs
 * @param a
 * @param b
 */
static __inline void swap(Square_t *a, Square_t *b)
{
    Square_t temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief
 * Runs a bubble sort on an array of Image_Location structs
 * based on the value of the 'info' field.
 * @param arr
 * @param n
 */
static void memory_bubble_sort(Square_t arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].random_num > arr[j + 1].random_num)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


/******************************************************************************
 * Public Functions 
 ******************************************************************************/

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
void staff_draw_image(uint8_t row, uint8_t col, mem_image_t image, uint16_t fcolor, uint16_t bcolor)
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
 * Initializes an array of Image_Location structs so that
 * there are 4 of each suit (hearts, diamonds, clubs, spades)
 * located in random locations on the board.
 *
 * This function assumes that the array is a 4x4 array.
 *
 * @param images
 */
void staff_randomize_images(Square_t *images)
{
    uint8_t row = 0;
    uint8_t col = 0;
    Square_t *current_image;

    /* Initialize the array with 4 hearts */
    images[0].image_type = MEM_IMAGE_HEART;
    images[0].fcolor = LCD_COLOR_RED;
    images[1].image_type = MEM_IMAGE_HEART;
    images[1].fcolor = LCD_COLOR_RED;
    images[2].image_type = MEM_IMAGE_HEART;
    images[2].fcolor = LCD_COLOR_RED;
    images[3].image_type = MEM_IMAGE_HEART;
    images[3].fcolor = LCD_COLOR_RED;

    /* Initialize the array with 4 diamonds */
    images[4].image_type = MEM_IMAGE_DIAMOND;
    images[4].fcolor = LCD_COLOR_RED;
    images[5].image_type = MEM_IMAGE_DIAMOND;
    images[5].fcolor = LCD_COLOR_RED;
    images[6].image_type = MEM_IMAGE_DIAMOND;
    images[6].fcolor = LCD_COLOR_RED;
    images[7].image_type = MEM_IMAGE_DIAMOND;
    images[7].fcolor = LCD_COLOR_RED;

    /* Initialize the array with 4 clubs */
    images[8].image_type = MEM_IMAGE_CLUB;
    images[8].fcolor = LCD_COLOR_BLUE;
    images[9].image_type = MEM_IMAGE_CLUB;
    images[9].fcolor = LCD_COLOR_BLUE;
    images[10].image_type = MEM_IMAGE_CLUB;
    images[10].fcolor = LCD_COLOR_BLUE;
    images[11].image_type = MEM_IMAGE_CLUB;
    images[11].fcolor = LCD_COLOR_BLUE;

    /* Initialize the array with 4 spades*/
    images[12].image_type = MEM_IMAGE_SPADE;
    images[12].fcolor = LCD_COLOR_BLUE;
    images[13].image_type = MEM_IMAGE_SPADE;
    images[13].fcolor = LCD_COLOR_BLUE;
    images[14].image_type = MEM_IMAGE_SPADE;
    images[14].fcolor = LCD_COLOR_BLUE;
    images[15].image_type = MEM_IMAGE_SPADE;
    images[15].fcolor = LCD_COLOR_BLUE;

    /* Initialize each square's random number*/
    for (int i = 0; i < 16; i++)
    {
        images[i].random_num = cyhal_trng_generate(&trng_obj);
        images[i].bcolor = LCD_COLOR_BLACK;
    }

    /* Sort the 16 Image_Locations based on their ID */
    memory_bubble_sort(images, 16);

    /* Assign the row and col based on their location in the sorted array */
    current_image = images;
    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            current_image->row = row;
            current_image->col = col;

            // Go to the next image in the array.
            current_image++;
        }
    }
}

/**
 * @brief
 * Prints out the grid of the game board
 * @param print_debug
 * If set to true, print out additional debug information about the location of the borders to
 * the serial console
 */
void staff_set_grid_color(uint16_t color)
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

#endif