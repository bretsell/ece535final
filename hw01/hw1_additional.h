/**
 * @file hw1_additional.h
 * @author Prateek Tandon, Bret Sell
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw01.h"

#ifndef _HW1Additional_
#define _HW1Additional_

// These three variables are used with the second timer

// MS_300 indicates we want to use the timer for 300 ms
extern bool MS_300;

// MS_1000 indicates we want to use the timer for 1s (1000ms)
extern bool MS_1000;

// Done is asserted once we have counted to that number of ms
extern bool done;

// Contains the actual address for the timer
extern cyhal_timer_t MS_10_timer;
extern cyhal_timer_cfg_t MS_10_timer_config;

// Draws 16 question marks to the screen.
// The row, col parameters are the current (active) square.
// This is useful so that we can invert the colors of the active square.
extern void draw_question_marks(uint8_t row, uint8_t col);

// Initializes all 16 spaces of memory.
// Assigns their image and color, and declares them hidden and not found
extern void initialize_memory(Square memory[4][4]);

// Checks to see if all of the squares have been found.
// If they have, then the game is over, and the player won!
extern bool checkVictory(Square memory[4][4]);

#endif