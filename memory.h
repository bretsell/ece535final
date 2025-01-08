/**
 * @file memory.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "memory_staff.h"

#if defined(HW02A)

extern cyhal_trng_t trng_obj;
extern volatile memory_event_t EVENT_IPC;

/******************************************************************************/
/* Function Declarations */
/******************************************************************************/

void memory_ack_send(void);
void memory_ack_wait(void);
bool memory_packet_verify(uint8_t *packet);
void memory_square_display(Square_t *square);
void memory_square_display_all(Square_t *squares);
void memory_square_transmit(Square_t *square, uint8_t remote_cmd_type);
void memory_square_transmit_all(Square_t *squares, uint8_t remote_cmd_type);




#endif
#endif