#include "task_imu.h"


#if defined(HW03A)

/**
 * @brief
 * The IMU Task will monitor the IMU every 100mS.  The IMU task is the ONLY task that is 
 * allowed to directly access the IMU device.
 * 
 * This task will determine when the IMU has been moved in the X or Y axis 
 * 
 * You should only inform the FSM that the joystick has been moved from the CENTER postion to 
 * UP, DOWN, RIGHT, or LEFT.  DO NOT report the IMU moving back to the CENTER. 
 * 
 * When the task determines that the IMU has been moved UP, DOWN, LEFT, or RIGHT, 
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
void task_imu(void *param)
{
  // See implementation in imu.c
  lsm6dsm_init();

  joystick_position_t posCurr = JOYSTICK_POS_CENTER;
  joystick_position_t posPrev = JOYSTICK_POS_CENTER;

  while (1)
  {
    // Poll every 100 ms
    vTaskDelay(100);

    // Get the current position (function MODIFIED IN imu.c to return joystick position)
    posCurr = lsm6dsm_orientation();

    // Check to see if we have moved away from center
    if (posCurr != JOYSTICK_POS_CENTER && posPrev == JOYSTICK_POS_CENTER) {
      task_print_info("TILT MOVEMENT DETECTED!");

      // Update the movement to the queue
      xQueueSendToBack(q_Dir, &posCurr, portMAX_DELAY);

      // Tell event queues that we had a move detected
      xEventGroupSetBits(eg_UI, EVENT_UI_MOVE);
    }

    // During the loop around, the current position becomes the previous position
    posPrev = posCurr;

  }
}



/*
  Initialize the imu task.
*/
void task_imu_init(void)
{
  spi_init();

    // Instantiate the IMU task
    xTaskCreate(
      task_imu,
      "Task IMU",
      configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_UI_INPUT,
      NULL);

 }

#endif