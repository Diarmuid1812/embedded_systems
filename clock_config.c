#include "stm32f4xx.h"
#include "stdio.h"
#include "clock_config.h"



void clockInit(int setting)
{
	if(setting==PLL)
	{
		// set up HSE, which will be used as a source
		// and wait until it's enabled
		RCC->CR |= RCC_CR_HSEON_Msk;
		while(!(RCC->CR&RCC_CR_HSERDY_Msk));

	/* PLL parameters:
		 *            input * plln
		 * output =  --------------
		 *            pllm * pllp  
		 *
		 * input = 8MHz (from HSE)
		 * 
		 * output = (8 * 100)/(2 * 4) = 100 [MHz]
		 */			

		// main multiplier -- * 100
		uint32_t plln = 100UL<<RCC_PLLCFGR_PLLN_Pos;
		
		// main divider -- /2
		uint32_t pllm = 2UL<<RCC_PLLCFGR_PLLM_Pos;
		
		// input divider flag
		// 0x01 configures divider to /4
		uint32_t pllp = 1UL<<RCC_PLLCFGR_PLLP_Pos;
		
		// Configure PLL with defined parameters
		// and HSE as the source
		RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE_Msk | plln | pllm | pllp;
		
		// Turn PLL on
		// and wait until it's enabled
		RCC->CR |= RCC_CR_PLLON_Msk;
		while(!(RCC->CR&RCC_CR_PLLRDY_Msk));
		
		// Set main system clock to PLL
		// and wait for settings to be applied
		RCC->CFGR &= ~RCC_CFGR_SW_Msk;
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		while((RCC->CFGR&RCC_CFGR_SWS_Msk)!=RCC_CFGR_SWS_PLL);

		printf("System clock set up to PLL, frequency 100MHz\n");

	}
	
	if(setting==HSE)
	{
		// Turn HSE on
		// and wait until it's enabled
		RCC->CR |= RCC_CR_HSEON_Msk;
		while(!(RCC->CR&RCC_CR_HSERDY_Msk));
		
		// Set main system clock to HSE
		// and wait for settings to be applied
		RCC->CFGR &= ~RCC_CFGR_SW_Msk;
		RCC->CFGR |= RCC_CFGR_SW_HSE<<RCC_CFGR_SW_Pos;
		while((RCC->CFGR&RCC_CFGR_SWS_Msk)!=RCC_CFGR_SWS_HSE);

		printf("System clock set up to high speed external clock (HSE)\n");
	}
	
	if(setting==HSI)
	{
		// Turn HSI on
		// and wait until it's enabled
		RCC->CR |= RCC_CR_HSION_Msk;
		while(!(RCC->CR&RCC_CR_HSIRDY_Msk));
		
		// Set main system clock to HSI
		// and wait for settings to be applied
		RCC->CFGR &= ~RCC_CFGR_SW_Msk;
		RCC->CFGR |= RCC_CFGR_SW_HSI<<RCC_CFGR_SW_Pos;
		while((RCC->CFGR&RCC_CFGR_SWS_Msk)!=(RCC_CFGR_SWS_HSI));

		printf("System clock set up to high speed internal clock (HSI)\n");
	}
	
	// Update SystemCoreClock variable
	// to reflect changes
	SystemCoreClockUpdate(); 	
}
