#ifndef __TASK_STATE_INIT_RECEIVE_H__
#define __TASK_STATE_INIT_RECEIVE_H__

#include "hw03.h"

#if defined(HW03A)

extern TaskHandle_t Task_Handle_State_Init_Receive;
void task_state_init_receive(void *param);
void task_state_init_receive_init(void);

#endif

#endif