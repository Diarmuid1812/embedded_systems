#include "stm32f4xx.h"
#include "peripherials_init.h"

void buttonInit(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
}

void ledInitDirectOutput()
{
	// Enable GPIOD
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	
	// Output mode for leds PD(12..15)
	GPIOD->MODER |= 1UL<<GPIO_MODER_MODE12_Pos;
	GPIOD->MODER |= 1UL<<GPIO_MODER_MODE13_Pos;
	GPIOD->MODER |= 1UL<<GPIO_MODER_MODE14_Pos;
	GPIOD->MODER |= 1UL<<GPIO_MODER_MODE15_Pos;
}

void ledInitPWM() {

	// Enable GPIOD
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	// Alternate function mode
	GPIOD->MODER |= 2UL<<GPIO_MODER_MODE12_Pos;
	GPIOD->MODER |= 2UL<<GPIO_MODER_MODE13_Pos;
	GPIOD->MODER |= 2UL<<GPIO_MODER_MODE14_Pos;
	GPIOD->MODER |= 2UL<<GPIO_MODER_MODE15_Pos;

	// Select AF2 (TIM4 channels 1-4)
	GPIOD->AFR[1] |= 2UL<<GPIO_AFRH_AFSEL12_Pos;
	GPIOD->AFR[1] |= 2UL<<GPIO_AFRH_AFSEL13_Pos;
	GPIOD->AFR[1] |= 2UL<<GPIO_AFRH_AFSEL14_Pos;
	GPIOD->AFR[1] |= 2UL<<GPIO_AFRH_AFSEL15_Pos;
}

void tim4Init() {
	// Enable Tim 4 peripheral
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	// Enable the PWM mode for channels 1-4
	TIM4->CCMR1 |= 7UL<<TIM_CCMR1_OC1M_Pos;
	TIM4->CCMR1 |= 7UL<<TIM_CCMR1_OC2M_Pos;

	TIM4->CCMR2 |= 7UL<<TIM_CCMR2_OC3M_Pos;
	TIM4->CCMR2 |= 7UL<<TIM_CCMR2_OC4M_Pos;

	// Enable preload registers
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE_Msk;
	TIM4->CCMR1 |= TIM_CCMR1_OC2PE_Msk;

	TIM4->CCMR2 |= TIM_CCMR2_OC3PE_Msk;
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE_Msk;

	// Enable output to pins for channels 1-4
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->CCER |= TIM_CCER_CC2E;
	TIM4->CCER |= TIM_CCER_CC3E;
	TIM4->CCER |= TIM_CCER_CC4E;


	// Set auto-reload
	//(maximum duty value for PWM)
	TIM4->ARR = 2000UL;
	// Set prescaler (divider for core clock)
	TIM4->PSC = 16UL;

	// Enable UG bit to update
	// register values
	// (timer safety feature
	//  prevents manipulating
	//  registers without buffering)
	TIM4->EGR |= TIM_EGR_UG;

	// Start timer counter
	TIM4->CR1 |= TIM_CR1_CEN;
}
