#ifndef __LED_H
#define __LED_H

#include "hk32f030m.h"

#define  LED1_ON     GPIOA->BRR  = GPIO_Pin_1;
#define  LED1_OFF    GPIOA->BSRR = GPIO_Pin_1;
#define  LED1_FILP   GPIOA->ODR ^= GPIO_Pin_1;

#define  LED_B_ON    GPIOC->BSRR = GPIO_Pin_7;
#define  LED_B_OFF   GPIOC->BRR  = GPIO_Pin_7;

#define  LED_F_ON    GPIOC->BSRR = GPIO_Pin_6;
#define  LED_F_OFF   GPIOC->BRR  = GPIO_Pin_6;

extern uint16_t LED_Counter;

void LED_Init(void);

#endif


