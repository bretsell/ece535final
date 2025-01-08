#include "task_state_init_receive.h"

#if defined(HW03A)

TaskHandle_t Task_Handle_State_Active;

/**
 * @brief
 * The ACTIVE task will sleep (blocked state) until a Task Notification is received.
 * 
 * When the ACTIVE task is woken up using the a Task Notification, it will will draw the LCD grid with
 * the active color. The ACTIVE task will update the game board to display the current location of the
 * active square
 *
 * The ACTIVE task will block on eg_UI until SW1 (EVENT_UI_SW1) has been pressed OR
 * the movement has been detected (EVENT_UI_MOVE).
 *
 * If EVENT_UI_MOVE is detected, the user can move the active square around the game board. All
 * movement information is received from q_Dir.  The active square must stay on the game board at 
 * all times, so make sure to check the boundary conditions. The active square is displayed by 
 * inverting the foreground and background colors.
 *
 * If EVENT_UI_SW1 is detected, the user can select the active square using SW1. If the active square 
 * is successfully selected, reveal the image at that location, send the remote player the coordinates, 
 * and wait for the ACK.
 *
 * If the active square has already been selected, turn on the buzzer (3.5Khz, 50% duty cycle) for 300mS
 *
 * Once the user has successfully selected two squares, check to see if the squares match.  If the
 * squares match, check to see if the game is over.  The game is over when all squares have been matched.
 * If the game is over, send a Task Notification to the Game Over task.  If both squares match but the game
 * is not over, remain in the ACTIVE task and allow the user to select additional squares.
 *
 * If the two selected squares do not match, show the selected images for 1 second (vTaskDelay(1000)) 
 * then send a Task Notification to the Waiting task and place the ACTIVE task into a blocked state 
 * waiting on a Task Notification.
 *
 * @param param
 */
void task_state_active(void *param)
{
  bool state_active = false;

  // This will hold the previous set of coordinates
  // {-1, -1} is used to hold the coordinates when no image has been previously selected
  uint8_t prevCoor[2] = {-1, -1};

  /* Suppress warning for unused parameter */
  (void)param;

  /* Repeatedly running part of the task */
  for (;;)
  {
    /* Wait for the task notification to wake up */
    ulTaskNotifyTake(true, portMAX_DELAY);
    state_active = true;

    task_print_info("Entering State ACTIVE ");

    /* Clear Any Past Events from the Event Group. This helps to prevent the situation where
       the user was pressing SW1 or moving the joystick in one of the other states*/
    xEventGroupClearBits(eg_UI, 0xFFFFFF);

    /* Clear any messages that were received when the application is not in the active state*/
    xQueueReset(q_Dir);
      
    while (state_active)
    {
      /* ADD CODE */

      // We just entered the active state, change the grid to active
      Square_t tempSquare;
      tempSquare.image_type = MEM_IMAGE_GRID_ACTIVE;
      xQueueSendToBack(q_LCD, &tempSquare, portMAX_DELAY);

      // Put current (active) square
      Game_Board[Row][Col].active = true;
      xQueueSendToBack(q_LCD, &Game_Board[Row][Col], portMAX_DELAY);



      // Wait until MOVE or SW1
      EventBits_t triggerBits = xEventGroupWaitBits(
          eg_UI, // What to test
          EVENT_UI_SW1 | EVENT_UI_MOVE, // What bits to wait for
          true, // Clear the bits before returning
          false, // Don't wait for both bits, either is fine
          portMAX_DELAY // How long to wait
      );

      if (triggerBits & EVENT_UI_SW1) {
        // SW1 Pressed

        // Was the selected square previously selected? Has it already been found?
        if (Game_Board[Row][Col].status != SQUARE_STATUS_NOT_SELECTED) {

          // Invalid image, play the buzzer
          pwm_buzzer_start();
          // Wait 300 ms
          vTaskDelay(300);
          pwm_buzzer_stop();
        }

        else {
          // New image selected


          // Draw new image
          Game_Board[Row][Col].status = SQUARE_STATUS_SELECTED;
          xQueueSendToBack(q_LCD, &Game_Board[Row][Col], portMAX_DELAY);

          // Send this square to the other board
          Remote_Uart_Data_t toSend;
          toSend.num_bytes = 6;
          toSend.payload[0] = REMOTE_CMD_PACKET_START;
          toSend.payload[1] = REMOTE_CMD_TYPE_SEL;
          toSend.payload[2] = Row;
          toSend.payload[3] = Col;
          toSend.payload[4] = Game_Board[Row][Col].image_type;
          toSend.payload[5] = REMOTE_CMD_PACKET_END;
          xQueueSendToBack(q_Remote_Tx, &toSend, portMAX_DELAY);

          // Wait for ACK
          task_print_info("Waiting for ACK...");
          triggerBits = xEventGroupWaitBits(
              eg_UI, // What to test
              EVENT_IPC_RX_ACK, // What bits to wait for
              true, // Clear the bits before returning
              false, // Don't wait for both bits, either is fine
              portMAX_DELAY // How long to wait
          );
          task_print_info("ACK Received");

          // Was that the first one selected?
          // Check to see how many squares have SQUARE_STATUS_SELECTED
          // (we have already put the current square as selected, so it should be 1 or 2 squares selected)
          uint8_t anotherSel = 0;
          for (uint8_t i = 0; i <= 3; i++) {
            for (uint8_t j = 0; j <= 3; j++) {
              if (Game_Board[i][j].status == SQUARE_STATUS_SELECTED) {
                anotherSel++;
                // Print the square that is "selected"
                task_print_info("%0d, %0d", i, j);
              }
            }
          }

          if (anotherSel == 1) {
            task_print_info("FIRST ONE SELECTED");
            prevCoor[0] = Row;
            prevCoor[1] = Col;
          }

          else {
            // Second one selected
            task_print_info("SECOND ONE SELECTED");
            task_print_info("%0d", prevCoor[0]);

            // Do they match?
            if (Game_Board[Row][Col].image_type == Game_Board[prevCoor[0]][prevCoor[1]].image_type) {
              // They matched!
              // Change their status to found
              Game_Board[Row][Col].status = SQUARE_STATUS_FOUND;
              Game_Board[prevCoor[0]][prevCoor[1]].status = SQUARE_STATUS_FOUND;

              // Update score
              Score++;
              task_print_info("Score is %0d", Score);
              xQueueSendToBack(q_IO_Exp, &Score, portMAX_DELAY);


              // Check to see if all of them match
              // (if they did, the game is over)
              bool allMatch = true;
              for (uint8_t row = 0; row <= 3; row++) {
                for (uint8_t col = 0; col <= 3; col++) {
                  if (Game_Board[row][col].status != SQUARE_STATUS_FOUND) allMatch = false;
                }
              }

              // Is the game over?
              if (allMatch) {
                task_print_info("THE GAME IS OVER");
                xTaskNotifyGive(Task_Handle_State_Game_Over);
                state_active = false;
              }
              else {
                task_print_info("The game was NOT seen as over");
              }
            }

            // (if statement is if Game_Board[prev]'s type == Game_Board[curr]'s type)
            else {
              // They did NOT match!
              
              // Wait for 1 second
              vTaskDelay(1000);

              // Revert the squares back to NOT_SELECTED
              Game_Board[Row][Col].status = SQUARE_STATUS_NOT_SELECTED;
              Game_Board[prevCoor[0]][prevCoor[1]].status = SQUARE_STATUS_NOT_SELECTED;
              xQueueSendToBack(q_LCD, &Game_Board[Row][Col], portMAX_DELAY);
              xQueueSendToBack(q_LCD, &Game_Board[prevCoor[0]][prevCoor[1]], portMAX_DELAY);

              // Go into waiting task
              xTaskNotifyGive(Task_Handle_State_Waiting);
              state_active = false;
            }

            // Reset prevCoor back to {-1, -1}
            prevCoor[0] = -1;
            prevCoor[1] = -1;
          }
        }
      }

      else if (triggerBits & EVENT_UI_MOVE) {
        // Joystick was moved (or IMU change was detected)

        // Get the joystick position
        joystick_position_t newActive;
        xQueueReceive(q_Dir, &newActive, portMAX_DELAY);

        // Switch the "Active" Square to no longer be active
        task_print_info("SWITCHING COLOR");
        Game_Board[Row][Col].active = false;
        xQueueSendToBack(q_LCD, &Game_Board[Row][Col], portMAX_DELAY);


        // Change row/col according to how the joystick position was changed
        switch (newActive) {
          case JOYSTICK_POS_LEFT: task_print_info("MOVING LEFT"); Col = (Col == 0) ? 0 : Col - 1; break;
          case JOYSTICK_POS_RIGHT: task_print_info("MOVING RIGHT"); Col = (Col == 3) ? 3 : Col + 1; break;
          case JOYSTICK_POS_UP: task_print_info("MOVING UP"); Row = (Row == 0) ? 0 : Row - 1; break;
          case JOYSTICK_POS_DOWN: task_print_info("MOVING DOWN"); Row = (Row == 3) ? 3 : Row + 1; break;
          default: task_print_info("INVALID JOYSTICK DETECTED");
        }

        // Swap new square color
        Game_Board[Row][Col].active = true;

        xQueueSendToBack(q_LCD, &Game_Board[Row][Col], portMAX_DELAY);
      }
    }
  }
}

void task_state_active_init(void)
{
  xTaskCreate(
      task_state_active,
      "Task State Active",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_FSM,
      &Task_Handle_State_Active);
}

#endif