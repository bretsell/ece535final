/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX02)

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: Ex02 - Memory Mapped IO";

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize hardware resources 
 */
void peripheral_init(void)
{
    /* There are no hardware resources to initialize*/
    push_buttons_init(false);
}

/**
 * @brief
 * This function implements the behavioral requirements for the application
 */
void main_app(void)
{
    uint32_t reg_val;

    /* Enter Infinite Loop*/
    while (1)
    {

    }
}
#endif
