#ifndef __TASK_STATE_INIT_SEND_H__
#define __TASK_STATE_INIT_SEND_H__

#include "hw03.h"

#if defined(HW03A)

extern TaskHandle_t Task_Handle_State_Init_Send;

void task_state_init_send(void *param);
void task_state_init_send_init(void);

#endif

#endif