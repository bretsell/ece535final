#ifndef __TASK_STATE_WAITING_H__
#define __TASK_STATE_WAITING_H__

#include "hw03.h"

#if defined(HW03A)

extern TaskHandle_t Task_Handle_State_Waiting;

void task_state_waiting(void *param);
void task_state_waiting_init(void);


#endif

#endif