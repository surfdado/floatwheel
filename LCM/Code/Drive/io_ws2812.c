#include "io_ws2812.h"

void IO_WS2812_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIOD->BSRR = GPIO_Pin_4;
}

/*		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4; 750ns
*/

/*
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4; 250ns
*/

/*
	void delay(uint16_t i)
	{
		while(i--);
	}
	i=250 120us
*/

void WS2812_0_Code(void)
{
	//250ns
	for(int i = 0; i != 3; ++i) {
		GPIOD->BSRR = GPIO_Pin_4;
		__ASM volatile("" ::: "memory");
	}

	GPIOD->BRR = GPIO_Pin_4;
}

void WS2812_1_Code(void)
{
	//750ns
	for(int i = 0; i != 8; ++i) {
		GPIOD->BSRR = GPIO_Pin_4;
		__ASM volatile("" ::: "memory");
	}

	GPIOD->BRR = GPIO_Pin_4;
}
