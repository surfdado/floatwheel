#include "flag_bit.h"

/*
	Power_Flag = 0; Just powered on.
	Power_Flag = 1; VESC booting up.
	Power_Flag = 2; VESC boot-up completed.
	Power_Flag = 3; VESC powered off, the board is powered by the charger.
*/
uint8_t Power_Flag = 0;
/*
	Charge_Flag = 0; Just powered on.
	Charge_Flag = 1; Ready for charging.
	Charge_Flag = 2; Charging in progress.
	Charge_Flag = 3; Battery fully charged.
*/
uint8_t Charge_Flag = 0;
/*
	Lightbar_Mode_Flag = 0; Just powered on.
	Lightbar_Mode_Flag = 1; Display battery level.
	Lightbar_Mode_Flag = 2; Do not display battery level.
*/
uint8_t WS2812_Display_Flag = 0;
/*
	Footpad_Activation_Flag = 0; Just powered on.
	Footpad_Activation_Flag = 1; Left 5 LEDs blue, Right 5 LEDs off (adc1 > 2.5V, adc2 < 2.5V).
	Footpad_Activation_Flag = 2; Left 5 LEDs off, Right 5 LEDs blue (adc1 < 2.5V, adc2 > 2.5V).
	Footpad_Activation_Flag = 3; All 10 LEDs blue (adc1 > 2.5V, adc2 > 2.5V).
	Footpad_Activation_Flag = 4; All 10 LEDs off.
	Footpad_Activation_Flag = 5; Flywheel mode, pattern
*/
uint8_t WS2812_Flag = 0;
/*
	WS2812_Inhibit = 0; Allow refresh of WS2812
	WS2812_Inhibit = 1; Inhibit refresh of WS2812
*/
uint8_t WS2812_Inhibit = 0;
/*
	0 to 100% battery level
*/
uint8_t Power_Display_Flag = 0;
/*
	Buzzer_Flag = 0; Just powered up
	Buzzer_Flag = 1；The buzzer doesn't sound
	Buzzer_Flag = 2；Buzzer rings
*/
uint8_t Buzzer_Flag = 0;

/*
	Usart_Flag = Vesc_Data_Ready
*/
uint8_t Vesc_Data_Ready = 0;

/*
	Time of buzzer ringing
*/
uint16_t Buzzer_Time = 0;

/*
	Charging timing
*/
uint16_t Charge_Time = 0;
/*
	Lighting
*/
uint16_t Flashlight_Time = 0;
/*
	Start time
*/
uint16_t Power_Time = 0;
/*
	Serial port communication
*/
uint16_t Usart_Time = 0;
/*
	ADC sampling time.
*/
uint16_t ADC_Time = 0;
/*
	Time the board has been idle (aka not running)
*/
uint16_t Idle_Time = 0;
/*
	Shutdown counter, milliseconds and minutes
*/
uint16_t Shutdown_Time_S = 0;
uint8_t Shutdown_Time_M = 0;
/*
	ADC1
*/
float ADC1_Val = 0;
/*
	ADC2
*/
float ADC2_Val = 0;
/*
	Charging Port Voltage
*/
float Charge_Voltage = 0;
/*
	Light_Profile = 0 Just powered on.
	Light_Profile = 1 Headlight bightness low, Lightpad brightness high, beep once
	Light_Profile = 2 Headlight bightness mid, Lightpad brightness mid, beep twice
	Light_Profile = 3 Headlight bightness high, Lightpad brightness low, beep thrice
*/
uint8_t Gear_Position = 0;
/*
	WS2812 Measurement
*/
uint8_t WS2812_Measure = 0;
/*
	 Buzzer frequency in BPM, beats per minute, ranging from 60 to 180, corresponding to a duty cycle of 70 to 100)
*/
uint8_t Buzzer_Frequency = 0;

/*
	 When the button is double-clicked without pressing it, the headlight stays on for 3 seconds.
*/
uint16_t Flashlight_Detection_Time = 0;
/*
	Charging current and voltage original values
*/
float Charge_Current = 0;
/*
	V_I = 0: Sampling charging current.
	V_I = 1: Sampling charging voltage.
*/
uint8_t V_I = 1;
/*
	Counter used while detecting end of charging
*/
uint16_t Shutdown_Cnt = 0;
/*
	Charger detection time.
*/
uint16_t Charger_Detection_1ms = 0;

/*
	The current brightness of the headlights, to slowly ramp up to target brightness
*/
int Current_Headlight_Brightness = 0;
int Target_Headlight_Brightness = 0;
