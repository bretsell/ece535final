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

#if defined(EX03)

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: Ex03 PSoC6 IO Ports";

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
    cy_rslt_t rslt;

    /* Initialize SW1 P6_3 as an input */

    /* Initialize Red LED P9_0 as an output*/


}

/**
 * @brief
 * This function implements the behavioral requirements for the application
 */
void main_app(void)
{
    while(1){
    };
}
#endif