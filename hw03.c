/**
 * @file hw01a.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw03.h"

#if defined(HW03A)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW03A";
char STUDENTS[] = "Prateek Tandon, Bret Sell";

Square_t Game_Board[4][4];
Square_t Images[16];
uint8_t Row = 0;
uint8_t Col = 0;
uint8_t Score = 0;

 cyhal_trng_t trng_obj;

/* Event Groups Shared by all of the states*/
EventGroupHandle_t eg_UI;

/* Queues */
QueueHandle_t q_Squares;
QueueHandle_t q_Dir;


/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);

    pwm_buzzer_init();
}


void tasks_peripheral_init(void)
{
    /* Initialize the Console Task */
    task_console_init();

    /* Initialize the LCD Task */
    task_lcd_init();

    /* Initialize the Buttons Tasks*/
    task_sw_init();


    /* Initialize the Remote UART Tasks*/
    task_remote_rx_init();
    task_remote_tx_init();

    /* Initialize the joystick Task*/
    task_joystick_init();

    /* Initialize the IMU Task*/ 
    task_imu_init();

    /* Initialize the IO Expander */
    task_io_expander_init();

}

void tasks_states_init(void)
{
    /* Initialize the Event Groups*/
    eg_UI = xEventGroupCreate();

    /* Initialize Queues*/
    q_Squares = xQueueCreate(1,sizeof(Square_t));
    q_Dir = xQueueCreate(1,sizeof(Direction_t));

    /* Initialize State Tasks */
    task_state_active_init();
    task_state_game_over_init();
    task_state_init_receive_init();
    task_state_init_send_init();
    task_state_player_sel_init();
    task_state_waiting_init();


}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void main_app(void)
{
    tasks_peripheral_init();

    tasks_states_init();

    /* Give Task Notify so that we start with the Player Select State*/
    xTaskNotifyGive(Task_Handle_State_Player_Sel);

    // Start the scheduler
    vTaskStartScheduler();

    /* RTOS scheduler exited */
    /* Halt the CPU if scheduler exits */
    CY_ASSERT(0);

    for (;;)
    {
    }
}

#endif
