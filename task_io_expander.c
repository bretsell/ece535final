#include "task_io_expander.h"

#if defined(HW03A)


// The queue we use to interact with this task
QueueHandle_t q_IO_Exp;

/**
 * @brief 
 * This file receives a score from one of the FSM tasks.  This score represents the number
 * of matches that the user has found. 
 * 
 * If the score is equal to 1, turn on the topmost RED LED.
 * If the score is equal to 2, turn on the topmost RED LED and the topmost Orange LED
 * If the score is equal to 3, turn on the topmost RED LED, the topmost Orange LED, and the yellow LED
 * .
 * .
 * .
 *  
 * @param param 
 * Not Used
 */
void task_io_expander(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    io_expander_set_configuration(0x80); 	// Set bit 7 as input, bits 6-0 as outputs 
	io_expander_set_output_port(0x00); 		// Turn OFF all LEDs

    // Helper variables we will use
    uint8_t io_exp = 0xFF;
    uint8_t theScore = 0;
    uint8_t LEDSig = 0x00;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */

        // When we get a new score, it should be put in q_IO_Exp for us to access
        // Thus sit and wait until we get an element
        xQueueReceive(q_IO_Exp, &theScore, portMAX_DELAY);

        task_print_info("SCORE DETECTED"); 

        // Read the input port
        io_exp = io_expander_get_input_port();

        // LED logic
        switch (theScore) {
            case 0: LEDSig = 0; break; // No LEDs are on
            case 1: LEDSig = 0x01; break; // Least Significant Bit LED is on
            case 2: LEDSig = 0x03; break; // The Two Least Significant LED bits are on
            case 3: LEDSig = 0x07; break; // The three least significant LED bits are on
            case 4: LEDSig = 0x0F; break; // etc...
            case 5: LEDSig = 0x1F; break;
            case 6: LEDSig = 0x3F; break;
            case 7: LEDSig = 0x7F; break;
            case 8: LEDSig = 0x7F; break; // In this case this board found all matches, and the game is over.
                                          // The model board still had 7 lights on, so that's what we do here

            default: LEDSig = 0x00; break; // If we somehow have a score that is not from 0-8, don't show any LED
        }

        // Write the specified LEDs to the board output
        io_expander_set_output_port(LEDSig); 

    }
}

// Initializes the io_expander task
void task_io_expander_init(void)
{

    i2c_init();

    // Initialize Queue
    q_IO_Exp = xQueueCreate(1, sizeof(uint8_t));

    // Initialize Task
    xTaskCreate(
        task_io_expander,
        "Task IO Expander",
        10 * configMINIMAL_STACK_SIZE,
        NULL,
        HW03_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif