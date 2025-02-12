#ifndef __TASK_H
#define __TASK_H

#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "flag_bit.h"
#include "vesc_uasrt.h"

//#define PINTV
//#define XRV
//#define GTV
//#define ADV
#define ADV2

#define USE_BUZZER

#ifdef uVISION
#if defined(PINTV) || defined(XRV)
#define   VTC6
#else
#ifdef ADV2
#define   S50S
#else
#define   P42A
#endif
#endif
#endif

#if defined(GTV)
#define   BATTERY_STRING      		18
#elif defined(PINTV) || defined(XRV)
#define   BATTERY_STRING      		15
#elif defined(ADV)
#define   BATTERY_STRING      		20
#define	  FULL_VOLTAGE	  			82
#define	  CHARGING_VOLTAGE	  		40
#endif

#define   SHUTDOWN_TIME		  		20
#define   VESC_RPM            		1000
#define   VESC_BOOT_TIME      		4000
#define   VESC_SHUTDOWN_TIME      	1000
#define   DUTY_CYCLE          		0.9
#define   VOLTAGE_RECEIPT     		0.02
#define	  CHARGE_COMMAND_TIME		1000 		// frequency of notifying the float package of current charge state
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200
#define   WS2812_1_BRIGHTNESS 		20
#define   WS2812_2_BRIGHTNESS 		10
#define   WS2812_3_BRIGHTNESS 		5
#define   CHARGE_CURRENT			0.12
#define   DETECTION_SWITCH_TIME     500
#define   CHARGER_DETECTION_DELAY	1000
#define   NUM_LEDS 					10
#define   DEFAULT_IDLE_MODE			0

void LED_Task(void);
void KEY1_Task(void);
void WS2812_Task(void);
void Power_Task(void);
void Charge_Task(void);
void Headlights_Task(void);
void Buzzer_Task(void);
void Usart_Task(void);
void ADC_Task(void);
void VESC_State_Task(void);
void Flashlight_Detection(void);

#endif



