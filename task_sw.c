#include "task_sw.h"

#if defined(HW03A)

/**
 * @brief
 * Function used to detect when SW1 has been pressed.  The task should detect the initial button 
 * press by debouncing the push button for 50mS.  Pressing the button for longer than 50mS should
 * only result in a single button event.
 * 
 * When the button press is detected, send EVENT_UI_SW1 to eg_UI
 * @param param
 *  Unused
 */
void task_sw1(void *param)
{
  uint8_t isPressed = 0;  // Counter to debounce the button press

  while (1)
  {
    uint32_t regVal = PORT_BUTTONS->IN; // Read input register to check button state
    vTaskDelay(25);
    if (!(regVal & SW1_MASK)) {
        isPressed = (isPressed > 4) ? 4 : isPressed + 1; 
        // Only at 50ms will we make the button pressed
        if (isPressed == 2) {            
            task_print_info("SW1 PRESSED");
            xEventGroupSetBits(eg_UI, EVENT_UI_SW1);  // Send button press event
        }
    }
    else {
        isPressed = 0;  // Reset counter if button is released
    }
  }
}
/**
 * @brief
 * Function used to detect when SW2 has been pressed.  The task should detect the initial button 
 * press by debouncing the push button for 50mS.  Pressing the button for longer than 50mS should
 * only result in a single button event.
 * 
 * When the button press is detected, send EVENT_UI_SW2 to eg_UI
 * @param param
 *  Unused
 */
void task_sw2(void *param)
{
  uint8_t isPressed = 0;  // Counter to debounce the button press
  
  while (1)
  {
    uint32_t regVal = PORT_BUTTONS->IN; // Read input register to check button state

    vTaskDelay(25);
    if (!(regVal & SW2_MASK)) {
        isPressed = (isPressed > 4) ? 4 : isPressed + 1; 
        // Only at 50ms will we make the button pressed
        if (isPressed == 2) {            
            task_print_info("SW2 PRESSED");
            xEventGroupSetBits(eg_UI, EVENT_UI_SW2);  // Send button press event
        }
    }
    else {
        isPressed = 0;  // Reset counter if button is released
    }
  }
}

/**
 * @brief
 * Initializes User Push Buttons and creates the corresponding FreeRTOS tasks for SW1 and SW2
 */
void task_sw_init(void)
{
  push_buttons_init(false);

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_sw1,
      "Task SW1",
      configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_UI_INPUT,
      NULL);

  xTaskCreate(
      task_sw2,
      "Task SW2",
      configMINIMAL_STACK_SIZE,
      NULL,
      HW03_TASK_PRIORITY_UI_INPUT,
      NULL);
}

#endif