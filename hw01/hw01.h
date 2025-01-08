/**
 * @file hw01.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-01-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HW01A__
#define __HW01A__

#include "../main.h"
#include "hw01_images.h"

#define HEIGHT_IMAGE                    40
#define HEIGHT_MARGIN_TIME_TOP          2
#define HEIGHT_TIME                     30
#define HEIGHT_MARGIN_TIME_BOTTOM       3
#define HEIGHT_BOARD                    198 
#define HEIGHT_MARGIN_BOARD_BOTTOM      5
#define HEIGHT_BORDER                   8 

#define WIDTH_IMAGE                     40
#define WIDTH_MARGIN_LEFT               60
#define WIDTH_BOARD                     198 
#define WIDTH_MARGIN_RIGHT              60
#define WIDTH_BORDER                    8 

/* Macros used to determine the vertical position of the images and game board borders */
#define LOC_Y_CENTER                    (240/2)
#define LOC_Y_TIME                      (HEIGHT_MARGIN_TIME_TOP + (HEIGHT_TIME/2) - 1)

#define LOC_Y_GAME_BOARD_CENTER         (LOC_Y_TIME + (HEIGHT_TIME/2) + HEIGHT_MARGIN_BOARD_BOTTOM + (HEIGHT_BOARD/2))

#define LOC_Y_BORDER_ROW0               (LOC_Y_TIME + (HEIGHT_TIME/2) + HEIGHT_MARGIN_TIME_BOTTOM + (HEIGHT_BORDER/2)) 
#define LOC_Y_IMAGE_ROW0                (LOC_Y_BORDER_ROW0 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW1               (LOC_Y_IMAGE_ROW0 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))
#define LOC_Y_IMAGE_ROW1                (LOC_Y_BORDER_ROW1 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW2               (LOC_Y_IMAGE_ROW1 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))
#define LOC_Y_IMAGE_ROW2                (LOC_Y_BORDER_ROW2 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW3               (LOC_Y_IMAGE_ROW2 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))
#define LOC_Y_IMAGE_ROW3                (LOC_Y_BORDER_ROW3 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW4               (LOC_Y_IMAGE_ROW3 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))


/* Macros used to determine the horizontal position of the images and game board boarders */
#define LOC_X_CENTER                    (320/2)

#define LOC_X_GAME_BOARD_CENTER         (LOC_X_CENTER)

#define LOC_X_BORDER_COL0               (WIDTH_MARGIN_LEFT + (WIDTH_BORDER/2) - 1)
#define LOC_X_IMAGE_COL0                (LOC_X_BORDER_COL0 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL1               (LOC_X_IMAGE_COL0 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))
#define LOC_X_IMAGE_COL1                (LOC_X_BORDER_COL1 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL2               (LOC_X_IMAGE_COL1 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))
#define LOC_X_IMAGE_COL2                (LOC_X_BORDER_COL2 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL3               (LOC_X_IMAGE_COL2 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))
#define LOC_X_IMAGE_COL3                (LOC_X_BORDER_COL3 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL4               (LOC_X_IMAGE_COL3 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))


typedef enum
{
    MEM_IMAGE_CLUB = 0,
    MEM_IMAGE_SPADE = 1,
    MEM_IMAGE_HEART = 2,
    MEM_IMAGE_DIAMOND = 3,
    MEM_IMAGE_QUESTION = 4
} mem_image_t;

/**
 * @brief 
 * Prints out the grid of the game board
 * @param print_debug 
 * If set to true, print out additional debug information about the location of the borders to 
 * the serial console
 */
void memory_draw_grid(bool print_debug);

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
void memory_draw_image(uint8_t row, uint8_t col, mem_image_t image, uint16_t fcolor, uint16_t bcolor);

/**
 * @brief 
 * Erases an image at the specified coordinates by drawing a black rectangle
 * @param row 
 * @param col 
 */
void memory_erase_image(uint8_t row, uint8_t col);

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
void memory_print_number(uint8_t num, uint16_t x, uint16_t y, uint16_t fcolor, uint16_t bcolor);

/** A particular square in the memory game.
 * @param hidden - a boolean that is whether the image is hidden (a question mark) or not hidden (their actual image)
 * @param theImage - stores the image this square is (club, heart, spade, diamond)
 * @param found - stores whether a match has been found for this square or not.
 * @param highlightColor - stores the color of the image. This is used for drawing the image and for when the image is selected.
*/
typedef struct {
    bool hidden;
    mem_image_t theImage;
    bool found;
    uint16_t highlightColor;
} Square;

#endif