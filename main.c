#include "stm32f4xx.h"
#include "stdio.h"
#include "clock_config.h"
#include "peripherials_init.h"
#include "PWM.h"

volatile uint32_t ticks;
void SysTick_Handler(void);
void delay(unsigned int);

void SysTick_Handler(void)  {
  if (ticks) ticks--;  
}

void delay(unsigned int delay)
{
	ticks = delay;
	// Wait until SysTickHandler
	// decreases ticks to 0
	while (delay>0) __NOP();
}



int main(void)
{
	// init
	FLASH->ACR |= 5;
	ledInitPWM();
	buttonInit();
	clockInit(HSI);
	SysTick_Config(SystemCoreClock/1000);
	tim4Init();

	// set channel 1 to 50% duty cycle
	pwm_SetDuty(50.0, 1);

	while(1) {

	}

	return 1;
}
