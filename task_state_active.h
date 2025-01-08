#ifndef __TASK_STATE_ACTIVE_H__
#define __TASK_STATE_ACTIVE_H__

#include "hw03.h"

#if defined(HW03A)

extern TaskHandle_t Task_Handle_State_Active;
void task_state_active(void *param);
void task_state_active_init(void);

#endif

#endif