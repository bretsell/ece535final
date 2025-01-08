/**
 * @file ice07.c
 * @author Bret Sell brsell@wisc.edu
 * @brief
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE01)
/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: ICE 01 - Intro to C";

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    /* There are no hardware resources to initialize in ICE01 */
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    printf("Hi, " );

    for (uint8_t i = 0; i < strlen(NAME); i++) {
        printf("%c", toupper(NAME[i]));
    }
    printf("!\nDone");
    printf("\n");
    
    /* Enter Infinite Loop*/
    while (1)
    {
    }
}
#endif