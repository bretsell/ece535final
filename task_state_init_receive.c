#include "task_state_init_receive.h"

#if defined(HW03A)

TaskHandle_t Task_Handle_State_Init_Receive;

/**
 * @brief
 * The Init Receive task is used to receive 16 squares from the remote board.
 *
 * This state will need to:
 *  1. Sleep (blocked state) until the task receives a Task Notification
 *  2. Receive a square from the remote board via q_Squares
 *  3. Send an Ack the remote board indicating that the packet has been received
 *  4. Each square will need to be drawn on the LCD
 *  5. Repeat Steps 1-4 until all 16 squares have been received
 *  6. Once all squares have been Acked and Displayed, send a Task Notification to task_state_inactive
 *  7. Return to step 1
 *
 * @param param
 */
void task_state_init_receive(void *param)
{
  /* Suppress warning for unused parameter */
  (void)param;
  bool state_active = false;

  /* Repeatedly running part of the task */
  for (;;)
  {
    /* Wait for the task notification to wake up */
    ulTaskNotifyTake(true, portMAX_DELAY);

    state_active = true;

    task_print_info("Entering State INIT_RECEIVE");

    /* Clear Any Past Events from the Event Group. This helps to prevent the situation where
   the user was pressing SW1 or moving the joystick in one of the other states*/
    xEventGroupClearBits(eg_UI, 0xFFFFFF);

    while(state_active)
    {
      Square_t sentSquare;\
      /* Receive and draw 16 squares */
      for (uint8_t row = 0; row <= 3; row++) {
        for (uint8_t col = 0; col <= 3; col++) {
          // Receive square from the remote board
          xQueueReceive(q_Squares, &sentSquare, portMAX_DELAY);

          // Send ACK
          Remote_Uart_Data_t sendACK;
          sendACK.num_bytes = 1;
          sendACK.payload[0] = REMOTE_CMD_ACK;
          xQueueSendToBack(q_Remote_Tx, &sendACK, portMAX_DELAY);

          // Draw square
          xQueueSendToBack(q_LCD, &sentSquare, portMAX_DELAY);

          // Store the received square in the game board
          Game_Board[row][col] = sentSquare;
        }

      }

      // All squares received, acknowledged, and drawn
      // Notify the waiting state task to proceed
      xTaskNotifyGive(Task_Handle_State_Waiting);
      state_active = false;

      // Reset score and update IO Expander
      Score = 0;
      xQueueSendToBack(q_IO_Exp, &Score, portMAX_DELAY);
    }
  }
}

  void task_state_init_receive_init(void)
  {
    xTaskCreate(
        task_state_init_receive,
        "Task State Init Rx",
        5 * configMINIMAL_STACK_SIZE,
        NULL,
        HW03_TASK_PRIORITY_FSM,
        &Task_Handle_State_Init_Receive);
  }
#endif