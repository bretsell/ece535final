/**
 * @file ice07.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX13)

char APP_DESCRIPTION[] = "ECE353: Example 13 - SPI IMU";

/*****************************************************************************/
/*  Function Declarations                                                    */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    spi_init();

    lsm6dsm_init();

}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    while (1)
    {
        /* This function will never return */
        lsm6dsm_orientation();
    }
}

#endif
