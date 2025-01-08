#include "task_joystick.h"

#if defined(HW03A)

/**
 * @brief
 * The Joystick Task will monitor the ADC channels connected to the joystick. The joystick
 * should be examined every 100mS.  The joystick task is the ONLY task that is allowed to
 * directly access the ADC peripheral.
 * 
 * This task will determine when the joystick has been moved out of the center position 
 * to either UP, DOWN, RIGHT, or LEFT. You should only inform the FSM that the joystick 
 * has been moved from the CENTER postion to UP, DOWN, RIGHT, or LEFT.  DO NOT report the 
 * joystick moving back to the CENTER. 
 * 
 * When the task determines that the joystick has been moved UP, DOWN, LEFT, or RIGHT, 
 * you will need to:
 * 
 *  1.) Send the current position to q_Dir 
 *  2.) Wake up the FSM by sending EVENT_UI_MOVE 
 * 
 * NOTE: You will need to send the joystick position to q_Dir first, 
 * THEN send then set the corresponding bit in eg_UI. 
 *  
 * @param param
 *  Unused
 */
void task_joystick(void *param)
{
  // Allocate current and previous position
  joystick_position_t posCurr = JOYSTICK_POS_CENTER;
  joystick_position_t posPrev = JOYSTICK_POS_CENTER;
  
  while (1)
  {
    /* The Joystick will be ready every 100mS*/
    vTaskDelay(100);

    // Get the joystick current position
    posCurr = joystick_get_pos();

    //Check if joystick has been moved from center position
    if (posCurr != JOYSTICK_POS_CENTER && posPrev == JOYSTICK_POS_CENTER) {
      task_print_info("JOYSTICK MOVEMENT DETECTED!");
      // Sends joystick position only when moved from center
      xQueueSendToBack(q_Dir, &posCurr, portMAX_DELAY);

      //Wake up the fsm
      xEventGroupSetBits(eg_UI, EVENT_UI_MOVE);
    }
    //assign previous position to current
    posPrev = posCurr;
  }
}

/**
 * @brief
 */
void task_joystick_init(void)
{
  joystick_init();

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_joystick,
      "Task Joystick",
      configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_UI_INPUT,
      NULL);
}

#endif