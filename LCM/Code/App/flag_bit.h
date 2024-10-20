#ifndef __FLAG_BIT_H
#define __FLAG_BIT_H

#include "hk32f030m.h"
#include "config.h"

extern uint8_t Power_Flag;
#ifdef HAS_CHARGING
extern uint8_t Charge_Flag;
#endif
#ifdef HAS_WS2812
extern uint8_t WS2812_Display_Flag;
extern uint8_t WS2812_Flag;
extern uint8_t Power_Display_Flag;
#endif
#ifdef USE_BUZZER
extern uint8_t Buzzer_Flag;
#endif
extern uint8_t Vesc_Data_Ready;

#ifdef USE_BUZZER
extern uint16_t Buzzer_Time;
#endif
extern uint16_t Charge_Time;
extern uint16_t Flashlight_Time;
extern uint16_t Power_Time;
extern uint16_t Usart_Time;
extern uint16_t ADC_Time;
extern uint16_t Idle_Time;
extern uint16_t Shutdown_Time_S;
extern uint8_t Shutdown_Time_M;

extern float ADC1_Val;
extern float ADC2_Val;
#ifdef HAS_CHARGING
extern float Charge_Voltage;
extern float Charge_Current;
extern uint8_t V_I;
extern uint16_t Charger_Detection_1ms;
#endif
extern uint8_t Gear_Position;
#ifdef HAS_WS2812
extern uint8_t WS2812_Measure;
#endif
#ifdef USE_BUZZER
extern uint8_t Buzzer_Frequency;
#endif
extern uint16_t Flashlight_Detection_Time;
extern uint16_t Shutdown_Cnt;

// Directional headlight brightness: positive = forward, negative = reverse
extern int Current_Headlight_Brightness;
extern int Target_Headlight_Brightness;

#endif
