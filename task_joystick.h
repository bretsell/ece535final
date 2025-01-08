#ifndef __TASK_JOYSTICK_H__
#define __TASK_JOYSTICK_H__

#include "hw03.h"

#if defined(HW03A)

extern QueueHandle_t q_Dir;

void task_joystick(void *param);
void task_joystick_init(void);

#endif

#endif
