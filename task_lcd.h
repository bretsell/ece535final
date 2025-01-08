#ifndef __TASK_LCD_H__
#define __TASK_LCD_H__

#include "hw03.h"

#if defined(HW03A)

extern QueueHandle_t q_LCD;

void task_lcd_init(void);
void task_lcd(void *param);

#endif

#endif
