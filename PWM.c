#include "stm32f4xx.h"
#include "stdio.h"
#include "PWM.h"
#include "rt_fp.h"

void _pwm_1SetDuty_raw(uint32_t duty_cycle)
{
	TIM4->CCR1 |= duty_cycle;
}

void _pwm_2SetDuty_raw(uint32_t duty_cycle)
{
	TIM4->CCR2 |= duty_cycle;
}

void _pwm_3SetDuty_raw(uint32_t duty_cycle)
{
	TIM4->CCR3 |= duty_cycle;
}

void _pwm_4SetDuty_raw(uint32_t duty_cycle)
{
	TIM4->CCR4 |= duty_cycle;
}

void pwm_SetDuty(double duty_cycle_percentage, uint8_t channel)
{
	// Assures percentage in range 0-100%, truncating exceeding values
	if (duty_cycle_percentage<0.0) duty_cycle_percentage=0.0;
	else if (duty_cycle_percentage>100.0) duty_cycle_percentage=100.0;
	
	// Converting percentage value to an actual
	// value to write to CCRx register
	
	double max_duty = TIM4->ARR;
	// _dfixu is arm specific explicit conversion from double to uint32_t
	uint32_t duty_register_value = _dfixu(max_duty*(duty_cycle_percentage/100));
	
	
	
	switch (channel){
		case 1:
			_pwm_1SetDuty_raw(duty_register_value);
			break;
		case 2:
			_pwm_2SetDuty_raw(duty_register_value);
			break;
		case 3:
			_pwm_3SetDuty_raw(duty_register_value);
			break;
		case 4:
			_pwm_4SetDuty_raw(duty_register_value);
			break;
		default:
			printf("Undefined channel number: %d\n", channel);
			printf("No changes applied");
	}
}
