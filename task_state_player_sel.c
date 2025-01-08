#include "task_state_player_sel.h"

#if defined(HW03A)

TaskHandle_t Task_Handle_State_Player_Sel;

/**
 * @brief
 * This state is used to determine if the board is player 1.  This state will remaining
 * in a blocked state until it receives a Task Notification to wake up.
 *
 * Once awake, there are two events that this state will respond to.
 *
 *    SW1 is pressed
 *      1. The local board will become Player1.
 *      2. Send a REMOTE_CMD_PLAYER1_SEL command to the remote board
 *      3. Wait for an ACK
 *      4. Send a Task Notification to task_state_init_send
 *      5 Sleep (blocked state) until the task receives a Task Notification
 *
 *    Receive a EVENT_IPC_RX_PLAYER1 from the remote UART
 *      1. Send a REMOTE_CMD_ACK to the remote board.
 *      2. Send a Task Notification to task_state_init_receive
 *      3. Sleep (blocked state) until the task receives a Task Notification
 *
 * Remember, you CANNOT directly access the remote UART or SW1 from this task.
 * You will need to send/receive data from the UART using the Queues/EventGroups
 * dedicated for this purpose
 *
 * @param param
 */
void task_state_player_sel(void *param)
{
  /* Suppress warning for unused parameter */
  (void)param;

  task_print("\x1b[2J\x1b[;H");
  task_print("**************************************************\n\r");
  task_print("* %s\n\r", APP_DESCRIPTION);
  task_print("* Date: %s\n\r", __DATE__);
  task_print("* Time: %s\n\r", __TIME__);
  task_print("* Names:%s\n\r", STUDENTS);
  task_print("**************************************************\n\r");

  /* Repeatedly running part of the task */
  for (;;)
  {
    /* Wait for the task notification to wake up */
    ulTaskNotifyTake(true, portMAX_DELAY);

    task_print_info("Entering State PLAYER_SEL");

    /* Clear Any Past Events from the Event Group. This helps to prevent the situation where
       the user was pressing SW1 or moving the joystick in one of the other states*/
    xEventGroupClearBits(eg_UI, 0xFFFFFF);

    /* Wait to recieve either sw1 or player1 */
    EventBits_t triggerBits = xEventGroupWaitBits(
      eg_UI, // What to test
      EVENT_UI_SW1 | EVENT_IPC_RX_PLAYER1, // What bits to wait for
      true, // Clear the bits before returning
      false, // Don't wait for both bits, either is fine
      portMAX_DELAY // How long to wait
    );

    //Sw1 detected
    if (triggerBits & EVENT_UI_SW1) {

      task_print_info("SW1 Detected Push");
      // Send REMOTE_CMD_PLAYER1_SEL
      Remote_Uart_Data_t toSend;
      toSend.num_bytes = 1;
      toSend.payload[0] = REMOTE_CMD_PLAYER1_SEL;
      xQueueSendToBack(q_Remote_Tx, &toSend, portMAX_DELAY);
      task_print_info("Given to UART");

      // Wait for ACK
      EventBits_t triggerBits = xEventGroupWaitBits(
        eg_UI, // What to test
        REMOTE_CMD_ACK, // What bits to wait for
        true, // Clear the bits before returning
        false, // Don't wait for both bits, either is fine
        portMAX_DELAY // How long to wait
      );
      task_print_info("ACK received");

      // Send notification to INIT_SEND
      xTaskNotifyGive(Task_Handle_State_Init_Send);
    }

    //Player 1 selected
    else if (triggerBits & EVENT_IPC_RX_PLAYER1 ) {
      // Send ACK
      Remote_Uart_Data_t toSend;
      toSend.num_bytes = 1;
      toSend.payload[0] = REMOTE_CMD_ACK;
      xQueueSendToBack(q_Remote_Tx, &toSend, portMAX_DELAY);

      // Go to INIT_RECEIVE
      xTaskNotifyGive(Task_Handle_State_Init_Receive);
    }
  }
}

/**
 * @brief
 * Initializes the Player Select Task
 */
void task_state_player_sel_init(void)
{
  xTaskCreate(
      task_state_player_sel,
      "Task State Player Sel",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_FSM,
      &Task_Handle_State_Player_Sel);
}
#endif