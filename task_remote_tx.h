#ifndef __TASK_REMOTE_TX_H__
#define __TASK_REMOTE_TX_H__

#include "hw03.h"

#if defined(HW03A)

extern QueueHandle_t q_Remote_Tx;

void task_remote_tx_init(void);
void task_remote_tx(void *param);

#endif

#endif