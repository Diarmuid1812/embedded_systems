#include "stm32f4xx.h"
#include "stdio.h"

void _pwm_1SetDuty_raw(uint32_t duty_cycle);

void _pwm_2SetDuty_raw(uint32_t duty_cycle);

void _pwm_3SetDuty_raw(uint32_t duty_cycle);

void _pwm_4SetDuty_raw(uint32_t duty_cycle);

void pwm_SetDuty(double duty_cycle_percentage, uint8_t channel);
