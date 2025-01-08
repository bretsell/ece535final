/**
 * @file systick.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "systick.h"

/**
 * @brief 
 *  Initilaizes the SysTick Timer for a configurable interval of time. 
 * @param ticks 
 *  The Number clock cycles 
 */
void systick_init(uint32_t ticks)
{
    if (ticks > 0xFFFFFF) return false; // Timer can only store 24 bits, anything greater causes problems

    // turn off SysTick timer
    SysTick->CTRL = 0;

    // Set current value to 0 (maybe we call SysTick multiple times, somewhere else it is a 1)
    SysTick->VAL = 0;

    // Set period
    SysTick->LOAD = ticks - 1; // Count down to 0, not the number of ticks

    // Set clock source to main CPU clock and turn timer on
    SysTick->CTRL = SYSTICK_CTRL_CLKSOURCE | SYSTICK_CTRL_ENABLE;

    return true;
}


bool systick_expired(void)
{
    if (SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG) {
        return true;
    }
    else return false;
}
