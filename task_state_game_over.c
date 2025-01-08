#include "task_state_game_over.h"

#if defined(HW03A)

TaskHandle_t Task_Handle_State_Game_Over;

/**
 * @brief
 * 
 * The GAME OVER task will sleep (blocked state) until a Task Notification is received.
 * 
 * The GAME OVER Task will display the game over image to the user by sending a Square_t structure
 * to the LCD Task where the image_type field type is set to  MEM_IMAGE_GAME_OVER
 *
 * The GAME OVER task also monitors eg_UI for EVENT_UI_SW2 and EVENT_IPC_RX_RESTART.
 *
 * If EVENT_UI_SW2 is detected
 *    1. The GAME OVER task will clear the LCD 
 *    2. The GAME OVER task will transmit REMOTE_CMD_RESTART to the remote board
 *    3. The GAME OVER task will wait for REMOTE_CMD_RESTART to be ACKED
 *    4. The GAME OVER task will send a Task Notification to the INIT SEND Task
 *    5. The GAME OVER task will move into a blocked state waiting for a Task Notification
 * 
 * If EVENT_IPC_RX_RESTART is detected, the GAME OVER task will clear the LCD and wake up the INIT RECEIVE task.
 *    1. The GAME OVER task will clear the LCD 
 *    2. The GAME OVER task will transmit REMOTE_CMD_ACK to the remote board
 *    3. The GAME OVER task will send a Task Notification to the INIT RECEIVE Task
 *    4. The GAME OVER task will move into a blocked state waiting for a Task Notification
 *
 * @param param
 */
void task_state_game_over(void *param)
{
  /* Suppress warning for unused parameter */
  (void)param;

  /* Repeatedly running part of the task */
  for (;;)
  {
    /* Wait for the task notification to wake up */
    ulTaskNotifyTake(true, portMAX_DELAY);

    task_print_info("Entering State Game Over ");

    /* Clear Any Past Events from the Event Group. This helps to prevent the situation where
   the user was pressing SW1 or moving the joystick in one of the other states*/
    xEventGroupClearBits(eg_UI, 0xFFFFFF);

    /* Create a structure to send the game over image to the LCD */
    Square_t toSend;
    toSend.image_type = MEM_IMAGE_GAME_OVER;
    xQueueSendToBack(q_LCD, &toSend, portMAX_DELAY);

    /* Wait for either SW2 press event or IPC restart event */
    EventBits_t triggerBits = xEventGroupWaitBits(
      eg_UI, // What to test
      EVENT_UI_SW2 | EVENT_IPC_RX_RESTART, // What bits to wait for
      true, // Clear the bits before returning
      false, // Don't wait for both bits, either is fine
      portMAX_DELAY // How long to wait
    );

    if (triggerBits & EVENT_UI_SW2) {
        // SW2 pressed event
        // Clear LCD
        toSend.image_type = MEM_IMAGE_LCD_RESET;
        xQueueSendToBack(q_LCD, &toSend, portMAX_DELAY);

        // Transmit REMOTE_CMD_RESTART
        Remote_Uart_Data_t restart;
        restart.num_bytes = 1;
        restart.payload[0] = REMOTE_CMD_RESTART;
        xQueueSendToBack(q_Remote_Tx, &restart, portMAX_DELAY);


        // Wait for ACK
        triggerBits = xEventGroupWaitBits(
          eg_UI,
          EVENT_IPC_RX_ACK,
          true,
          false,
          portMAX_DELAY
        );

        // Go to INIT_SENT
        xTaskNotifyGive(Task_Handle_State_Init_Send);

    }

    else if (triggerBits & EVENT_IPC_RX_RESTART) {
        // IPC restart event
        // Clear LCD
        toSend.image_type = MEM_IMAGE_LCD_RESET;
        xQueueSendToBack(q_LCD, &toSend, portMAX_DELAY);

        // Transmit REMOTE_CMD_ACK
        Remote_Uart_Data_t restart;
        restart.num_bytes = 1;
        restart.payload[0] = REMOTE_CMD_ACK;
        xQueueSendToBack(q_Remote_Tx, &restart, portMAX_DELAY);


        // Go to INIT_RECEIVE
        xTaskNotifyGive(Task_Handle_State_Init_Receive);

    }


  }
}

void task_state_game_over_init(void)
{
  xTaskCreate(
      task_state_game_over,
      "Task State Game Over",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_FSM,
      &Task_Handle_State_Game_Over);
}
#endif