#include "task_state_init_send.h"

#if defined(HW03A)

TaskHandle_t Task_Handle_State_Init_Send;

/******************************************************************************
 * Static Functions
 *
 * These Functions should never be called outside of this file
 ******************************************************************************/

/**
 * @brief
 * Swaps two Image_Location structs
 * @param a
 * @param b
 */
static __inline void swap(Square_t *a, Square_t *b)
{
    Square_t temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief
 * Runs a bubble sort on an array of Image_Location structs
 * based on the value of the 'info' field.
 * @param arr
 * @param n
 */
static void memory_bubble_sort(Square_t arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].random_num > arr[j + 1].random_num)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/**
 * @brief
 * Initializes an array of Image_Location structs so that
 * there are 4 of each suit (hearts, diamonds, clubs, spades)
 * located in random locations on the board.
 *
 * This function assumes that the array is a 4x4 array.
 *
 * @param images
 */
static void staff_randomize_images(Square_t *images)
{
    uint8_t row = 0;
    uint8_t col = 0;
    Square_t *current_image;

    /* Initialize the array with 4 hearts */
    images[0].image_type = MEM_IMAGE_HEART;
    images[0].fcolor = LCD_COLOR_RED;
    images[1].image_type = MEM_IMAGE_HEART;
    images[1].fcolor = LCD_COLOR_RED;
    images[2].image_type = MEM_IMAGE_HEART;
    images[2].fcolor = LCD_COLOR_RED;
    images[3].image_type = MEM_IMAGE_HEART;
    images[3].fcolor = LCD_COLOR_RED;

    /* Initialize the array with 4 diamonds */
    images[4].image_type = MEM_IMAGE_DIAMOND;
    images[4].fcolor = LCD_COLOR_RED;
    images[5].image_type = MEM_IMAGE_DIAMOND;
    images[5].fcolor = LCD_COLOR_RED;
    images[6].image_type = MEM_IMAGE_DIAMOND;
    images[6].fcolor = LCD_COLOR_RED;
    images[7].image_type = MEM_IMAGE_DIAMOND;
    images[7].fcolor = LCD_COLOR_RED;

    /* Initialize the array with 4 clubs */
    images[8].image_type = MEM_IMAGE_CLUB;
    images[8].fcolor = LCD_COLOR_BLUE;
    images[9].image_type = MEM_IMAGE_CLUB;
    images[9].fcolor = LCD_COLOR_BLUE;
    images[10].image_type = MEM_IMAGE_CLUB;
    images[10].fcolor = LCD_COLOR_BLUE;
    images[11].image_type = MEM_IMAGE_CLUB;
    images[11].fcolor = LCD_COLOR_BLUE;

    /* Initialize the array with 4 spades*/
    images[12].image_type = MEM_IMAGE_SPADE;
    images[12].fcolor = LCD_COLOR_BLUE;
    images[13].image_type = MEM_IMAGE_SPADE;
    images[13].fcolor = LCD_COLOR_BLUE;
    images[14].image_type = MEM_IMAGE_SPADE;
    images[14].fcolor = LCD_COLOR_BLUE;
    images[15].image_type = MEM_IMAGE_SPADE;
    images[15].fcolor = LCD_COLOR_BLUE;

    /* Initialize each square's random number*/
    for (int i = 0; i < 16; i++)
    {
        images[i].random_num = cyhal_trng_generate(&trng_obj);
        images[i].bcolor = LCD_COLOR_BLACK;
    }

    /* Sort the 16 Image_Locations based on their ID */
    memory_bubble_sort(images, 16);

    /* Assign the row and col based on their location in the sorted array */
    current_image = images;
    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            current_image->row = row;
            current_image->col = col;
            current_image->active = false;
            current_image->status = SQUARE_STATUS_NOT_SELECTED;

            // Go to the next image in the array.
            current_image++;
        }
    }
}
/******************************************************************************
 * End of Static Functions
 ******************************************************************************/

/**
 * @brief
 * The Init Send state is used to initialize the locations of each image on
 * the game board.  This information is stored locally AND transmitted to the
 * remote board.
 *
 * This state will need to:
 *  1. Sleep (blocked state) until the task receives a Task Notification
 *  2. Generate the locations of all 16 squares.
 *  3. Transmit each square one at a time to the remote board.
 *  4. Each square will need to be ACKed before transmitting the next square.
 *  5. Each square will need to be drawn on the LCD
 *  6. Once all squares have been transmitted, send a Task Notification to task_state_active
 *  7. Return to step 1
 *
 *
 * @param param
 */
void task_state_init_send(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* Wait for the task notification to wake up */
        ulTaskNotifyTake(true, portMAX_DELAY);

        task_print_info("Entering State INIT_SEND");

        /*  Clear Any Past Events from the Event Group. This helps to prevent the situation where
            the user was pressing SW1 or moving the joystick in one of the other states*/
        xEventGroupClearBits(eg_UI, 0xFFFFFF);

        /* Generate the image locations */
        staff_randomize_images(Images);

         /* Transmit each square to the remote board and draw it on the LCD */
        for (uint8_t row = 0; row <= 3; row++) {
            for (uint8_t col = 0; col <= 3; col++) {
                // Assign image
                Game_Board[row][col] = Images[4*row + col];

                // Prepare packet to transmit to the remote board
                Remote_Uart_Data_t packet;
                packet.num_bytes = 6;
                packet.payload[0] = REMOTE_CMD_PACKET_START;
                packet.payload[1] = REMOTE_CMD_TYPE_INIT;
                packet.payload[2] = row;
                packet.payload[3] = col;
                packet.payload[4] = Game_Board[row][col].image_type;
                packet.payload[5] = REMOTE_CMD_PACKET_END;
                
                //Send the image
                xQueueSendToBack(q_Remote_Tx, &packet, portMAX_DELAY);

                // Wait for ACK
                EventBits_t triggerBits = xEventGroupWaitBits(
                    eg_UI, // What to test
                    EVENT_IPC_RX_ACK, // What bits to wait for
                    true, // Clear the bits before returning
                    false, // Don't wait for both bits, either is fine
                    portMAX_DELAY // How long to wait
                );

                // Draw image
                xQueueSendToBack(q_LCD, &Game_Board[row][col], portMAX_DELAY);

                //Reset the score and update IO expander
                Score = 0;
                xQueueSendToBack(q_IO_Exp, &Score, portMAX_DELAY);
            }
        }

        // Everything was transmitted
        xTaskNotifyGive(Task_Handle_State_Active);

    }
}

void task_state_init_send_init(void)
{
    xTaskCreate(
        task_state_init_send,
        "Task State Init Send",
        5 * configMINIMAL_STACK_SIZE,
        NULL,
        HW03_TASK_PRIORITY_FSM,
        &Task_Handle_State_Init_Send);
}
#endif