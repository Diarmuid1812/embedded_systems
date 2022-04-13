#include "stm32f4xx.h"
#include "stdio.h"
#include "LEDs.h"

void switchLed(unsigned int led_num){
	
	// reset all LEDs
	GPIOD->ODR &= ~(GPIO_ODR_OD15_Msk|GPIO_ODR_OD14_Msk|GPIO_ODR_OD13_Msk|GPIO_ODR_OD12_Msk);
	
	// Turn the desired LED on
	switch (led_num) {
		case 0:
			GPIOD->ODR |= GPIO_ODR_OD12_Msk;
			break;
		case 1:
			GPIOD->ODR |= GPIO_ODR_OD13_Msk;
			break;
		case 2:
			GPIOD->ODR |= GPIO_ODR_OD14_Msk;
			break;
		case 3:
			GPIOD->ODR |= GPIO_ODR_OD15_Msk;
			break;
		default:
			printf("Invalid led number: %d", led_num);
	}
}