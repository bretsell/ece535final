/**
 * @file memory.c
 * @author FILL IN YOU NAME(s) 
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "memory.h"

#if defined(HW02A)


/******************************************************************************
 * Functions that you will need to complete
 ******************************************************************************/

/**
 * @brief 
 * Sends REMOTE_CMD_ACK to the remote board
 */
void memory_ack_send(void)
{
    remote_uart_tx_char_async(REMOTE_CMD_ACK);
}

/**
 * @brief 
 * Waits to receive an REMOTE_CMD_ACK  
 */
void memory_ack_wait(void)
{
    while (EVENT_IPC != EVENT_IPC_RX_ACK) {};
    EVENT_IPC = EVENT_NONE;
}

/**
 * @brief
 * Verifies that the data received in the data packet are valid
 * @param packet
 * An array of 6 bytes received from the remote board
 * @return true
 * All bytes are valid
 * @return false
 * Packet contained invalid data
 */
bool memory_packet_verify(uint8_t *packet)
{
    if (packet[0] != REMOTE_CMD_PACKET_START) return false;
    if (packet[1] != REMOTE_CMD_TYPE_INIT && packet[1] != REMOTE_CMD_TYPE_SEL) return false;
    if (packet[2] < 0 || packet[2] > 3) return false;
    if (packet[3] < 0 || packet[3] > 3) return false;
    if (packet[4] < 0 || packet[4] > 6) return false;
    if (packet[5] != REMOTE_CMD_PACKET_END) return false;
    return true;
}

/**
 * @brief
 * Transmit data to the remote board. The format of the data being transmitted is as follows:
 *
 *       REMOTE_CMD_START
 *       REMOTE_CMD_TYPE_INIT or REMOTE_CMD_TYPE_SEL
 *       row
 *       col
 *       image
 *       REMOTE_CMD_END
 *
 * @param square 
 *     Data Structure that contains the information about the square to transmit 
 * @param remote_cmd_type
 *      Indicates if the square is being initialized or if the square was selected
 *      by the user
 */
void memory_square_transmit(Square_t *square, uint8_t remote_cmd_type)
{
    remote_uart_tx_char_async(REMOTE_CMD_PACKET_START);
    remote_uart_tx_char_async(remote_cmd_type);
    remote_uart_tx_char_async((*square).row);
    remote_uart_tx_char_async((*square).col);
    remote_uart_tx_char_async((*square).image_type);
    remote_uart_tx_char_async(REMOTE_CMD_PACKET_END);
}

/**
 * @brief
 * Transmits 16 images to the remote board.  
 * 
 * After each of the squares is transmitted, wait until REMOTE_CMD_ACK byte 
 * is received.
 * 
 * @param squares 
 * A array of 16 Square_t structs that contain the information needed to transmit the
 * images to the remote device.
 */
void memory_square_transmit_all(Square_t *squares, uint8_t remote_cmd_type)
{
    for (uint8_t i = 0; i < 16; i++) {
        memory_square_transmit(&squares[i], remote_cmd_type);
        memory_ack_wait();
    }
}

/**
 * @brief
 * Draws a single square to the LCD.
 * @param square
 * A pointer to the square to be displayed.
 */
void memory_square_display(Square_t *square)
{
    printf("Being used");
    staff_draw_image((*square).row, (*square).col, (*square).image_type, (*square).fcolor, (*square).bcolor);
}

/**
 * @brief
 * Draws the game board and all of the squares that were randomly generated.
 * @param squares
 * A array of 16 Square_t structs that contain the information needed to draw the
 * images at each location in the game board.
 */
void memory_square_display_all(Square_t *squares)
{
    for (uint8_t i = 0; i < 16; i++) {
        memory_square_display(&squares[i]);
    }
}


#endif