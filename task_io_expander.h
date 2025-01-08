#ifndef __TASK_IO_EXPANDER_H__
#define __TASK_IO_EXPANDER_H__

#include "hw03.h"

#if defined(HW03A)

extern QueueHandle_t q_IO_Exp;

void task_io_expander_init(void);
void task_io_expander(void *param);

#endif

#endif
