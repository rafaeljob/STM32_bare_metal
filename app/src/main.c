//////////////////////////////////////////////
//  File    : main.c
//  Dev by  : Rafael Basso
//////////////////////////////////////////////


//	INCLUDE
//////////////////////////////////////////////

#include "main.h"

//	FUNCTION
//////////////////////////////////////////////

// Static functions
static void SystemClock_Config(void);

// Main program
int main()
{
	uint32_t i;

	// Configure System Clock
	SystemClock_Config();

	// Initialize Debug Console
	BSP_Console_Init();
	bm_printf("# Console ready\r\n");

	// Initialize and start ADC on PC1
	BSP_ADC_Init();
	bm_printf("# ADC ready\r\n");

	// Initialize LED & Button pin
	BSP_LED_Init();
	bm_printf("# Led ready\r\n");

	BSP_PB_Init();
	bm_printf("# Push-button ready\r\n");

	// Main loop
	while(1)
	{
		// If User-Button is pushed down
		if (BSP_PB_GetState() == 1) { BSP_LED_On(); }
		else
		{
			BSP_LED_Off();
			// Wait here until ADC EOC
			while ((ADC1->ISR & ADC_ISR_EOC) != ADC_ISR_EOC);

			// Report result to console
			bm_printf("\tADC value = %d\r\n", ADC1->DR);

			// Wait about 200ms
			for (i=0; i<500000; i++);
		}
	}
}


// Clock configuration for the Nucleo STM32F072RB board
// HSE input Bypass Mode            -> 8MHz
// SYSCLK, AHB, APB1                -> 48MHz
// PA8 as MCO with /16 prescaler    -> 3MHz
static void SystemClock_Config()
{
	uint32_t	HSE_Status;
	uint32_t	PLL_Status;
	uint32_t	SW_Status;
	uint32_t	timeout = 0;

	timeout = 1000000;

	// Start HSE in Bypass Mode
	RCC->CR |= RCC_CR_HSEBYP;
	RCC->CR |= RCC_CR_HSEON;

	// Wait until HSE is ready
	do
	{
		HSE_Status = RCC->CR & RCC_CR_HSERDY_Msk;
		timeout--;
	} while ((HSE_Status == 0) && (timeout > 0));

	// Select HSE as PLL input source
	RCC->CFGR &= ~RCC_CFGR_PLLSRC_Msk;
	RCC->CFGR |= (0x02 <<RCC_CFGR_PLLSRC_Pos);

	// Set PLL PREDIV to /1
	RCC->CFGR2 = 0x00000000;

	// Set PLL MUL to x6
	RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;
	RCC->CFGR |= (0x04 <<RCC_CFGR_PLLMUL_Pos);

	// Enable the main PLL
	RCC-> CR |= RCC_CR_PLLON;

	// Wait until PLL is ready
	do
	{
		PLL_Status = RCC->CR & RCC_CR_PLLRDY_Msk;
		timeout--;
	} while ((PLL_Status == 0) && (timeout > 0));

        // Set AHB prescaler to /1
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	//Set APB1 prescaler to /1
	RCC->CFGR &= ~RCC_CFGR_PPRE_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE_DIV1;

	// Enable FLASH Prefetch Buffer and set Flash Latency
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

	// Select the main PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait until PLL becomes main switch input
	do
	{
		SW_Status = (RCC->CFGR & RCC_CFGR_SWS_Msk);
		timeout--;
	} while ((SW_Status != RCC_CFGR_SWS_PLL) && (timeout > 0));

	// Update SystemCoreClock global variable
	SystemCoreClockUpdate();
}
