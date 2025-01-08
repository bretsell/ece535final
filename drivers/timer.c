#include "timer.h"

void timer_init(cyhal_timer_t *timer_obj, cyhal_timer_cfg_t *timer_cfg, uint32_t ticks, void *Handler)
{
    cy_rslt_t rslt = CY_RSLT_SUCCESS;

    timer_cfg->compare_value = 0;
    timer_cfg->period = ticks - 1;
    timer_cfg->direction = CYHAL_TIMER_DIR_UP;
    timer_cfg->is_compare = false;
    timer_cfg->is_continuous = true;
    timer_cfg->value = 0;

    /* ADD CODE */
    /* Initialize a timer */
    rslt = cyhal_timer_init(timer_obj, NC, NULL);
    
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* ADD CODE */
    /* Apply timer configuration such as period, count direction, run mode, etc. */
    rslt = cyhal_timer_configure(timer_obj, timer_cfg);
   
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* ADD CODE */
    /* Set the frequency of timer*/
    rslt = cyhal_timer_set_frequency(timer_obj, 100000000); // FIND OUT WHAT TO SET
  
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* ADD CODE */
    /* Assign the ISR to execute on timer interrupt */
    cyhal_timer_register_callback(timer_obj, Handler, NULL);

    /* ADD CODE */
    /* Set the event on which timer interrupt occurs and enable it */
    cyhal_timer_enable_event(timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 4, true);

    /* ADD CODE */
    /* Start the timer with the configured settings */
    rslt = cyhal_timer_start(timer_obj);
    
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU
  
}
