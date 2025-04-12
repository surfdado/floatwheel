#ifndef CELLBALANCE_H__
#define CELLBALANCE_H__

#include "DVC11XX.h"
#include "Voltage.h"
#include "Temperature.h"

#define BALANCE_VOLTAGE_MIN 4180  //均衡最大电芯电压 mV
#define BALANCE_VOLTAGE_MAX_DELTA 0001	// mV

extern u32 newBals;

float DVC11XX_Calc_ChipTemp(void);
void Balance_Contrl(u32 vlaue);
void OverTempProtect(u8 temp);
void BalanceProcess(void);
void CalcuVolMaxMin(void);

#endif

