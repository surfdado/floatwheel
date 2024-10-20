#ifndef __CONFIG_H
#define __CONFIG_H

// NOTE: These are defined in the uVision target settings
// #define GTV
// #define PINTV
// #define XRV

#if !defined(GTV) && !defined(PINTV) && !defined(XRV)
#define HAS_CHARGING
#endif

#if !defined(XRV)
#define HAS_WS2812
#endif

// #define USE_BUZZER
#ifdef USE_BUZZER
#define BEEP_ON_POWER
#define BEEP_ON_DUTY_CYCLE
#endif

#endif
