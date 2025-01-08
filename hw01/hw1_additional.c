/**
 * @file hw1_additional.c
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

// Holds the logic behind our new timer.

/** 
	Draws 16 Question Marks to the screen.
	This will be used on initialization and restarts.
*/
void draw_question_marks(uint8_t row, uint8_t col) {
	for (uint8_t x = 0; x < 4; x++) {
		for (uint8_t y = 0; y < 4; y++) {
            // If x = row and y = col, then this square is the active square.
            // Thus we need to invert the colors
			if (x == row && y == col) memory_draw_image(x, y, MEM_IMAGE_QUESTION, LCD_COLOR_BLACK, LCD_COLOR_GREEN);

            // Otherwise just draw a question mark with the proper colors
			else memory_draw_image(x, y, MEM_IMAGE_QUESTION, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
		}
	}
}

// Assigns images/colors to all of the squares and makes them hidden / not found
void initialize_memory(Square memory[4][4]) {

    // This array is based off of the HW01C expected shape behavior.
    // if the top left square was meant to be a club, then allImages[0][0] contains MEM_IMAGE_CLUB.
    // Similarly for all of the images
    mem_image_t allImages[4][4] = { {MEM_IMAGE_CLUB, MEM_IMAGE_HEART, MEM_IMAGE_SPADE, MEM_IMAGE_HEART}, 
                                    {MEM_IMAGE_SPADE, MEM_IMAGE_DIAMOND, MEM_IMAGE_DIAMOND, MEM_IMAGE_CLUB}, 
                                    {MEM_IMAGE_HEART, MEM_IMAGE_SPADE, MEM_IMAGE_DIAMOND, MEM_IMAGE_HEART}, 
                                    {MEM_IMAGE_SPADE, MEM_IMAGE_CLUB, MEM_IMAGE_CLUB, MEM_IMAGE_DIAMOND} };
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {

            // These images start off being hidden and not found
            memory[i][j].hidden = true;
            memory[i][j].found = false;

            // allImages[row][col] contains the correct shape for memory[row][col]
            memory[i][j].theImage = allImages[i][j];

            // Clubs and Spades should be blue
            if (allImages[i][j] == MEM_IMAGE_CLUB || allImages[i][j] == MEM_IMAGE_SPADE) memory[i][j].highlightColor = LCD_COLOR_BLUE;

            // Otherwise they should be red
            else memory[i][j].highlightColor = LCD_COLOR_RED;
        }
    }
}


// Checks to see if the user has completed the game
bool checkVictory(Square memory[4][4]) {
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            // The game is over once every element has been found.
            // Thus if we find a single square that has not been found, the game is not over.
            if (memory[i][j].found == false) return false;
        }
    }
    // If we are here, no image has NOT been found.
    // Thus the game is over, so return true
    return true;
}