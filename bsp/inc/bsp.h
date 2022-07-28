//////////////////////////////////////////////
//  File    : bsp.h
//  Dev by  : Rafael Basso
//////////////////////////////////////////////

#ifndef __BSP_H__
#define __BSP_H__

//  INCLUDE
//////////////////////////////////////////////

#include "stm32f0xx.h"

//  FUNCTION
//////////////////////////////////////////////

//  LED driver functions
void BSP_LED_Init(void);
void BSP_LED_On(void);
void BSP_LED_Off(void);
void BSP_LED_Toggle(void);

//  BUTTON driver functions
void BSP_PB_Init(void);
uint8_t BSP_PB_GetState(void);

#endif /* __BSP_H__ */
