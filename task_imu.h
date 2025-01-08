#ifndef __TASK_IMU_H__
#define __TASK_IMU_H__

#include "hw03.h"

#if defined(HW03A)

extern QueueHandle_t q_Dir;

void task_imu(void *param);
void task_imu_init(void);

#endif

#endif
