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

#if defined(EX01)

char APP_DESCRIPTION[] = "ECE353: Ex01 - Intro to C";

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
    /* There are no hardware resources to initialize in ICE01 */
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
    int32_t ArrayA[20];
    int32_t ArrayB[20];
    int8_t count = 0;

    for(int8_t i = 0; i < 20; i++)
    {
        ArrayA[i] = rand();
        ArrayB[i] = rand();
    }

    for(int8_t i = 0; i < 20; i++)
    {
        if(ArrayA[i] > ArrayB[i]){
            count++;
        }
    }

    printf("count : %d\n\r", count);
    /* Enter Infinite Loop*/
    while (1)
    {
    }
}
#endif
