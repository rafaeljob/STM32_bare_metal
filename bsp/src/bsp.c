//////////////////////////////////////////////
//  File    : bsp.c
//  Dev by  : Rafael Basso
//////////////////////////////////////////////


//	INCLUDE
//////////////////////////////////////////////
#include "bsp.h"

//	FUNCTION
//////////////////////////////////////////////

//	Initialize LED pin (PA5) as a High-Speed Push-Pull output
//	Set LED initial state to OFF
void BSP_LED_Init(void)
{
	// Enable GPIOA clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Configure PA5 as output
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->MODER |= (0x01 <<GPIO_MODER_MODER5_Pos);

	// Configure PA5 as Push-Pull output
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;

	// Configure PA5 as High-Speed Output
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR5_Msk;
	GPIOA->OSPEEDR |= (0x03 <<GPIO_OSPEEDR_OSPEEDR5_Pos);

	// Disable PA5 Pull-up/Pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5_Msk;

	// Set Initial State OFF
	GPIOA->BSRR |= GPIO_BSRR_BR_5;
}

//	Turn ON LED on PA5
void BSP_LED_On(void) { GPIOA->BSRR = GPIO_BSRR_BS_5; }

//	Turn OFF LED on PA5
void BSP_LED_Off(void) { GPIOA->BSRR = GPIO_BSRR_BR_5; }

//	Toggle LED on PA5
void BSP_LED_Toggle(void) { GPIOA->ODR ^= GPIO_ODR_5; }


//	Initialize Push-Button pin (PC13) as input without Pull-up/Pull-down
void BSP_PB_Init()
{
	// Enable GPIOC clock
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	// Configure PC13 as input
	GPIOC->MODER &= ~GPIO_MODER_MODER13_Msk;
	GPIOC->MODER |= (0x00 <<GPIO_MODER_MODER13_Pos);

	// Disable PC13 Pull-up/Pull-down
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13_Msk;
}

//	Returns the state of the button (0=released, 1=pressed)
uint8_t BSP_PB_GetState()
{
	uint8_t state;

	if ((GPIOC->IDR & GPIO_IDR_13) == GPIO_IDR_13)
	{
		state = 0;
	}
	else
	{
		state = 1;
	}

	return state;
}


