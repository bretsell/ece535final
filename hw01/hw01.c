/**
 * @file hw01.c
 * @author Prateek Tandon, Bret Sell
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "hw01.h"

/**
 * @brief
 * Prints out the grid of the game board
 * @param print_debug
 * If set to true, print out additional debug information about the location of the borders to
 * the serial console
 */
void memory_draw_grid(bool print_debug)
{
    /* Clear the game board area */
    lcd_draw_rectangle_centered(
        LOC_X_GAME_BOARD_CENTER,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BOARD,
        HEIGHT_BOARD,
        LCD_COLOR_BLACK);

    if (print_debug)
    {
        /* Print out the location of each of the horizontal lines */
        printf("Time is located at (%d,%d)\n\r", LOC_X_CENTER, LOC_Y_TIME);
        printf("Row0 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_X_CENTER, LOC_Y_BORDER_ROW0, WIDTH_BOARD, HEIGHT_BORDER);
        printf("Row1 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_X_CENTER, LOC_Y_BORDER_ROW1, WIDTH_BOARD, HEIGHT_BORDER);
        printf("Row2 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_X_CENTER, LOC_Y_BORDER_ROW2, WIDTH_BOARD, HEIGHT_BORDER);
        printf("Row3 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_X_CENTER, LOC_Y_BORDER_ROW3, WIDTH_BOARD, HEIGHT_BORDER);
        printf("Row4 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_X_CENTER, LOC_Y_BORDER_ROW4, WIDTH_BOARD, HEIGHT_BORDER);
    }

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW0,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        LCD_COLOR_ORANGE);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW1,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        LCD_COLOR_ORANGE);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW2,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        LCD_COLOR_ORANGE);

    lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW3,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        LCD_COLOR_ORANGE);
 
     lcd_draw_rectangle_centered(
        LOC_X_CENTER,
        LOC_Y_BORDER_ROW4,
        WIDTH_BOARD,
        HEIGHT_BORDER,
        LCD_COLOR_ORANGE);
    
    /* Draw the horizontal Lines on the screen */

    if (print_debug)
    {
        /* Print out the location of each of the vertical lines */
        printf("Col0 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_Y_BORDER_ROW0, LOC_Y_CENTER, WIDTH_BORDER, HEIGHT_BOARD);
        printf("Col1 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_Y_BORDER_ROW1, LOC_Y_CENTER, WIDTH_BORDER, HEIGHT_BOARD);
        printf("Col2 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_Y_BORDER_ROW2, LOC_Y_CENTER, WIDTH_BORDER, HEIGHT_BOARD);
        printf("Col3 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_Y_BORDER_ROW3, LOC_Y_CENTER, WIDTH_BORDER, HEIGHT_BOARD);
        printf("Col4 is located at (%d,%d) with dimensions of (%d,%d) pixels\n\r", LOC_Y_BORDER_ROW4, LOC_Y_CENTER, WIDTH_BORDER, HEIGHT_BOARD);
    }

    /* Draw the vertical lines on the screen */
    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL0,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        LCD_COLOR_ORANGE);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL1,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        LCD_COLOR_ORANGE);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL2,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        LCD_COLOR_ORANGE);
        
    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL3,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        LCD_COLOR_ORANGE);

    lcd_draw_rectangle_centered(
        LOC_X_BORDER_COL4,
        LOC_Y_GAME_BOARD_CENTER,
        WIDTH_BORDER,
        HEIGHT_BOARD,
        LCD_COLOR_ORANGE);

}

/**
 * @brief 
 *  Prints out a single decimal number at the specified coordinates.  
 * @param num 
 *      Number to Print
 * @param x
 *      X coordinate 
 * @param y 
 *      Y coordinate
 * @param fcolor 
 *      Foreground color
 * @param bcolor 
 *      Background color
 */
void memory_print_number(uint8_t num, uint16_t x, uint16_t y, uint16_t fcolor, uint16_t bcolor)
{
    uint32_t bitmap_addr = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    /* Verify num is a number from 0-9 OR the ASCII character ':' */
    if( ((num >= 0) && ( num <= 9)) || (num == 58) )
    {
        /* If num is a ':', then we need to change the index into the LUT to be 10*/
        if(num == 58)
        {
            num = 10;
        }

        /* Get the height of the bitmap from the Font Look Up Table */
        height = Shentox_Desc[num].h_px;

        /* Get the width of the bitmap from the Font Look Up Table */
        width = Shentox_Desc[num].w_px;

        /* Get the address of the bitmap from the Font Look Up Table */
        bitmap_addr = (uint32_t)(&IMAGE_NUMBERS[Shentox_Desc[num].index]);

        lcd_draw_image(x, y, width, height, (const uint8_t *)bitmap_addr, fcolor, bcolor);
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
void memory_draw_image(uint8_t row, uint8_t col, mem_image_t image, uint16_t fcolor, uint16_t bcolor)
{
    // x_images[] is meant to hold all of the column values.
    // This is so that instead of having 4 if statements, we can do everything in one line
    // If col = 0, we pick x_images[0] which has LOC_X_IMAGE_COL0.
    // If col = 1, we pick x_images[1] which has LOC_IMAGE_COL1. etc.
    // Similar logic is put for y_images
    uint16_t x_images [4] = {LOC_X_IMAGE_COL0, LOC_X_IMAGE_COL1, LOC_X_IMAGE_COL2, LOC_X_IMAGE_COL3};
    uint16_t y_images [4] = {LOC_Y_IMAGE_ROW0, LOC_Y_IMAGE_ROW1, LOC_Y_IMAGE_ROW2, LOC_Y_IMAGE_ROW3};

    // To quickly check all of the possible images, we use a switch statement for readability
    // x_images[] and y_images[] was explained above.
    // We also set width and height to the pixel width/height specified in hw01_images.c
    // fcolor and bcolor are taken as is and do not require any modifications
    switch (image) {
        case MEM_IMAGE_CLUB:
            lcd_draw_image(x_images[col], y_images[row], 
                    IMAGE_CLUB_PIXEL_WIDTH, IMAGE_CLUB_PIXEL_HEIGHT, 
                    IMAGE_CLUB, fcolor, bcolor);
            
            // We are done, so exit the program
            return;
        
        case MEM_IMAGE_SPADE:
            lcd_draw_image(x_images[col], y_images[row], 
                    IMAGE_SPADE_PIXEL_WIDTH, IMAGE_SPADE_PIXEL_HEIGHT, 
                    IMAGE_SPADE, fcolor, bcolor);

            // We are done, so exit the program
            return;

        case MEM_IMAGE_HEART:
            lcd_draw_image(x_images[col], y_images[row], 
                    IMAGE_HEART_PIXEL_WIDTH, IMAGE_HEART_PIXEL_HEIGHT, 
                    IMAGE_HEART, fcolor, bcolor);

            // We are done, so exit the program
            return;

        case MEM_IMAGE_DIAMOND:
            lcd_draw_image(x_images[col], y_images[row], 
                    IMAGE_DIAMOND_PIXEL_WIDTH, IMAGE_DIAMOND_PIXEL_HEIGHT, 
                    IMAGE_DIAMOND, fcolor, bcolor);

            // We are done, so exit the program
            return;
        
        case MEM_IMAGE_QUESTION: 
            // This should not run for HW01A but technically is a possibility
            lcd_draw_image(x_images[col], y_images[row], 
                    IMAGE_QUESTION_PIXEL_WIDTH, IMAGE_QUESTION_PIXEL_HEIGHT, 
                    IMAGE_QUESTION, fcolor, bcolor);

            // We are done, so exit the program
            return;

        default: return; // This should never run, if it does we just display nothing
    }

}

/**
 * @brief 
 * Erases an image at the specified coordinates by drawing a black rectangle
 * @param row 
 * @param col 
 */
void memory_erase_image(uint8_t row, uint8_t col)
{
    // Similar to the above function, we use x_images[] and y_images[]
    // x_images[] is meant to hold all of the column values.
    // This is so that instead of having 4 if statements, we can do everything in one line
    // If col = 0, we pick x_images[0] which has LOC_X_IMAGE_COL0.
    // If col = 1, we pick x_images[1] which has LOC_X_IMAGE_COL1. etc.
    // Similar logic is put for y_images
    uint16_t x_images [4] = {LOC_X_IMAGE_COL0, LOC_X_IMAGE_COL1, LOC_X_IMAGE_COL2, LOC_X_IMAGE_COL3};
    uint16_t y_images [4] = {LOC_Y_IMAGE_ROW0, LOC_Y_IMAGE_ROW1, LOC_Y_IMAGE_ROW2, LOC_Y_IMAGE_ROW3};

    // "Erasing" an image is just replacing it with a black rectangle that takes up the whole part
    lcd_draw_rectangle_centered(
        x_images[col],
        y_images[row],
        WIDTH_IMAGE,
        HEIGHT_IMAGE,
        LCD_COLOR_BLACK);
}