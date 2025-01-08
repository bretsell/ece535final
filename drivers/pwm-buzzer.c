/**
 * @file pwm-buzzer.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "pwm-buzzer.h"

cyhal_pwm_t pwm_buzzer_obj;

void pwm_buzzer_init(void)
{
    // Initialize PWM on the supplied pin and assign a new clock
    cy_rslt_t rslt;
    rslt = cyhal_pwm_init(&pwm_buzzer_obj, PIN_IO_BUZZER, NULL);

    // Set a duty cycle of 50% and frequency of 3.5kHz
    cyhal_pwm_set_duty_cycle(&pwm_buzzer_obj, PWM_BUZZER_DUTY, PWM_BUZZER_FREQ);

}

void pwm_buzzer_start(void)
{
    /* (Re-)start the PWM output */
    cyhal_pwm_start(&pwm_buzzer_obj);
}

void pwm_buzzer_stop(void)
{
    /* Stop the PWM output */
    cyhal_pwm_stop(&pwm_buzzer_obj);

}



