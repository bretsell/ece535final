#include "task_state_init_receive.h"

#if defined(HW03A)

TaskHandle_t Task_Handle_State_Waiting;

/**
 * @brief
 * When the WAITING task is woken up using the a Task Notification, it will will draw the LCD grid with 
 * the inactive color. The WAITING task will update the game board so that none of the squares are 
 * displayed as the active square.
 *  
 * The WAITING task will then wait to receive squares from q_Squares. 
 * When a square is received, send an ACK to the remote board and then display the image on the LCD.
 * 
 * When two squares have been received, check to see if the squares match.
 * 
 * If the two squares match, determine if the game is over. If the game is over, send a Task Notification to
 * the Game Over Task.  If the two squares match but the game is not over, then remain in the WAITING
 * task.
 *
 * If the two squares do not match, display the images for 1 second and then send a Task Notification 
 * to ACTIVE task, and place the WAITING task into a blocked state waiting on a Task Notification.
 *  
 * @param param
 */
void task_state_waiting(void *param)
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
    task_print_info("Entering State WAITING ");

    /* Clear Any Past Events from the Event Group. This helps to prevent the situation where
       the user was pressing SW1 or moving the joystick in one of the other states*/
    xEventGroupClearBits(eg_UI, 0xFFFFFF);

    Square_t firstSquare;
    Square_t secondSquare;
    Square_t tempSquare;
    while(state_active)
    {

      /* ADD CODE */
      //Set the grid to be inactive color
      tempSquare.image_type = MEM_IMAGE_GRID_INACTIVE;
      xQueueSendToBack(q_LCD, &tempSquare, portMAX_DELAY);

      //Updates game board with no squares being active
      for (uint8_t row = 0; row <= 3; row++) {
        for (uint8_t col = 0; col <= 3; col++) {
          if (Game_Board[row][col].active) {
            Game_Board[row][col].active = false;
            xQueueSendToBack(q_LCD, &Game_Board[row][col], portMAX_DELAY);
          }
        }
      }

      // Image #1
      xQueueReceive(q_Squares, &firstSquare, portMAX_DELAY);
      task_print_info(firstSquare.status == SQUARE_STATUS_SELECTED);

      //Transmit the ack
      Remote_Uart_Data_t sendACK;
      sendACK.num_bytes = 1;
      sendACK.payload[0] = REMOTE_CMD_ACK;
      xQueueSendToBack(q_Remote_Tx, &sendACK, portMAX_DELAY);

      //Print Image 1
      firstSquare.status = SQUARE_STATUS_SELECTED;
      xQueueSendToBack(q_LCD, &firstSquare, portMAX_DELAY);

      task_print_info("IMAGE RECEIVED");

      // Image #2
      xQueueReceive(q_Squares, &secondSquare, portMAX_DELAY);

      task_print_info("IMAGE RECEIVED");

      //Transmit second square ack
      xQueueSendToBack(q_Remote_Tx, &sendACK, portMAX_DELAY);

      task_print_info(secondSquare.status == SQUARE_STATUS_SELECTED);

      //print the second square on the LCD Board
      secondSquare.status = SQUARE_STATUS_SELECTED;
      xQueueSendToBack(q_LCD, &secondSquare, portMAX_DELAY);


      //Check if these two squares match
      if (firstSquare.image_type == secondSquare.image_type) {
        //Set the status to each square as found as we now have a match
        Game_Board[firstSquare.row][firstSquare.col].status = SQUARE_STATUS_FOUND;
        Game_Board[secondSquare.row][secondSquare.col].status = SQUARE_STATUS_FOUND;

          // Check to see if all Squares have the status of found
          bool allMatch = true;
          for (uint8_t row = 0; row <= 3; row++) {
            for (uint8_t col = 0; col <= 3; col++) {
                if (Game_Board[row][col].status != SQUARE_STATUS_FOUND) allMatch = false;
            }
          }

          //if all squares match, set state to game over
          if (allMatch) {
            task_print_info("THE GAME IS OVER");
            xTaskNotifyGive(Task_Handle_State_Game_Over);
            state_active = false;
          }
          else {
            task_print_info("The game was NOT seen as over");
          }
      }
      else {
        // Did NOT match, Show squares for 1s
        vTaskDelay(1000);
        //Set squares back to question marks
        Game_Board[firstSquare.row][firstSquare.col].status = SQUARE_STATUS_NOT_SELECTED;
        Game_Board[secondSquare.row][secondSquare.col].status = SQUARE_STATUS_NOT_SELECTED;
        xQueueSendToBack(q_LCD, &Game_Board[firstSquare.row][firstSquare.col], portMAX_DELAY);
        xQueueSendToBack(q_LCD, &Game_Board[secondSquare.row][secondSquare.col], portMAX_DELAY);

        // Go into active
        xTaskNotifyGive(Task_Handle_State_Active);
        state_active = false;
      }
    }
  }
}

void task_state_waiting_init(void)
{
  xTaskCreate(
      task_state_waiting,
      "Task State Waiting",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_FSM,
      &Task_Handle_State_Waiting);
}
#endif