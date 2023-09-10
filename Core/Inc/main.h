#include <stdio.h>
#include "system_stm32h7xx.h"
#include "stm32h7xx.h"
#include "stm32h743xx.h"
#include "core_cm7.h"

#define TIM_EnableIT_UPDATE(TIMx) 	TIMx -> DIER |= TIM_DIER_UIE
#define TIM_EnableCounter(TIMx)		TIMx -> CR1 |= TIM_CR1_CEN

#define PIN1_ON()	GPIOB -> BSRR |= GPIO_BSRR_BS1;
#define PIN1_OFF()	GPIOB -> BSRR |= GPIO_BSRR_BR1;


static void GPIOInit(void);

static void SYS_Init(void);

static void Tim_Init(void);

//static void TIM3_IRQHandler(void);

#ifndef __MAIN_H

#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif







#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
