#ifndef __TASK_STATE_PLAYER_SEL_H__
#define __TASK_STATE_PLAYER_SEL_H__

#include "hw03.h"

#if defined(HW03A)

extern TaskHandle_t Task_Handle_State_Player_Sel;

void task_state_player_sel(void *param);
void task_state_player_sel_init(void);

#endif

#endif