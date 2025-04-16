/**
  ******************************************************************************
  * @file       ： main.c
  * @author     :  FCZ
  * @version    ： V1.1.6
  * @date       ： 2022年03月28日
  * @brief      ： 主函数 - LCM灯控
  * @mcu        :  HK32F030MF4P6
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2022-03-28 V1.0.0:初始版本
  2022-05-16 增加开机显示进度条和充电显示电压
  2022-05-17 更改充电显示为呼吸灯效果
  2022-06-09 关机时间由5分钟改为15分钟 
             占空比由超过70%改为超过80%蜂鸣器“哔”“哔”的响
			 自动关机条件由原来的不踩脚踏板增加一条且转速低于1000才开始计时关机
  2022-07-19 电池由12串改为20串
             关机时间改为30分钟
			 充电器电压检测加平均值滤波，电压判断加回执电压范围
  2023-01-16 WS2812驱动由硬件SPI模拟改为IO口加延时模拟
  ----------------------------------------------------------------------------*/
#include "hk32f030m.h"
#include "led.h"
#include "time.h"
#include "spi.h"
#include "ws2812.h"
#include "power.h"
#include "key.h"
#include "usart.h"
#include "adc.h"
#include "buzzer.h"
#include "led_pwm.h"
#include "test.h"
#include "task.h"
#include "io_ws2812.h"
#include "iwdg.h"

//RCC_ClocksTypeDef RCC_Clock;

/*
										
*/

/**************************************************
 * @brie   :main()
 * @note   :主函数
 * @param  :无
 * @retval :无
 **************************************************/
int main(void)
{	
	//RCC_GetClocksFreq(&RCC_Clock);
	LED_Init();
#ifdef USE_BUZZER		
	Buzzer_Init();
#endif
	ADC1_Init();
#ifdef ADV2
	Time6_Init();
#endif
	WS2812_Init();

#ifdef ADV2
	Power_Time = 0;
	while (Power_Time < 500) {
		__WFI();
	}
#endif

	Power_Init();
	KEY_Init();
	USART1_Init(115200);
	LED_PWM_Init();
#ifndef ADV2
	Time6_Init();
#endif
#ifdef IWDG_DEBUG
	IWDG_Init();
#endif
#ifndef ADV2
	if(KEY1 ==  0)
	{
#endif
		KEY1_State = 1;
#ifndef ADV2
	}
#endif

#ifdef ADV2
	Charge_Voltage = 3.3;
	Power_Time = 0;
#endif

	while(1)
	{
#ifdef ADV2
		LED_Task();
#endif
		KEY1_Task();
		
		if(WS2812_Counter >= 20) // 20ms refresh period
		{
			WS2812_Task();
			WS2812_Counter = 0;
		}

		Power_Task();

#ifdef ADV
		Charge_Task();
#endif
#ifdef ADV2
		Charge_Detect_Task();
#endif
		Headlights_Task();
#ifdef USE_BUZZER		
		Buzzer_Task();
#endif
		Usart_Task();
		ADC_Task();
		VESC_State_Task();
#ifdef IWDG_DEBUG
		IWDG_ReloadCounter();
#endif
	}
	return 0;
}
