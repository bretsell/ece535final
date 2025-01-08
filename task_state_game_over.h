#ifndef __TASK_STATE_GAME_OVER_H__
#define __TASK_STATE_GAME_OVER_H__

#include "hw03.h"

#if defined(HW03A)

extern TaskHandle_t Task_Handle_State_Game_Over;

void task_state_game_over(void *param);
void task_state_game_over_init(void);

#endif

#endif