#include "BMS_Protection.h"
#include "DVC11XX.h"
#include "flag.h"
#include "vesc_can.h"
#include "key.h"
#include "mos.h"
#include "CellBalance.h"
#include "charger.h"
#include "DVC1124_app.h"
#include "ppm.h"

/**************************************************
 * @brie  :BMS_Overvoltage_Protection()
 * @note  :过压保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Overvoltage_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0,val1 = 0;
	static uint8_t lock = 0;
	
	if(lock == 0)
	{
		for(i=0;i<AFE_MAX_CELL_CNT;i++)
		{
			if(DVC_1124.Single_Voltage[i] > 4200)
			{
				val1++;
			}
		}
	}
	else
	{
		val1 = 0xFF; //已经发生过压
	}
	
	if(val1 == 0)	//没有发生欠压
	{
		Software_Counter_1ms.Overvoltage_Protection_Delay = 0;
	}
	
	if(val1 == 0xFF)	//已经发生欠压
	{
		Software_Counter_1ms.Overvoltage_Protection_Delay = 65535;
	}	
	//if(g_AfeRegs.R0.bitmap.COV)		//发生电池过压
	if((val1 != 0) && (Software_Counter_1ms.Overvoltage_Protection_Delay > 1000))	//发生过压并保持1S
	{
		lock = 1;
		CHARG_OFF;					//关闭充电器
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[3] = 9900;	//错误代码
		Flag.Overvoltage = 1;
		
		if(newBals == 0)	//过压保护解除
		{
			lock = 0;
			Flag.Overvoltage = 0;
			if((CHARGER == 1) && (Flag.Charging_Overcurrent == 0)) //过压保护解除并且没有发生充电过流
			{
				if((Flag.Overtemperature == 0) && (Flag.Lowtemperature == 0))	//没有发生过温和低温
				{
					Flag.Charger_ON = 0;
				}
				
			}
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[3] = 0;	//错误代码
			
			r0 = g_AfeRegs.R0.cleanflag;
			clean_flag &= ~(1<<6);
			g_AfeRegs.R0.cleanflag = clean_flag;
			
			while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
			{
				i++;
			}
			g_AfeRegs.R0.cleanflag = r0;
		}
	}
}

/**************************************************
 * @brie  :BMS_Undervoltage_Protection()
 * @note  :欠压保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Undervoltage_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0,val1 = 0,val2 = 0,val3 = 0;
	static uint8_t lock = 0;
	
	for(i=0;i<AFE_MAX_CELL_CNT;i++)
	{
		if(DVC_1124.Single_Voltage[i] < 2300)
		{
			val3++;
		}
	}
	
	if(val3 != 0)	//有电芯电压低于2.3V 直接关机
	{
		DSG_OFF;
		CHG_OFF;
		CHG_OFF;
		PDSG_OFF;
		PCHG_OFF;
		Flag.Power = 3;
		return;
	}
		
	if(lock == 0)
	{
		for(i=0;i<AFE_MAX_CELL_CNT;i++)
		{
			if(DVC_1124.Single_Voltage[i] < 2700)
			{
				val1++;
			}
		}
	}
	else
	{
		val1 = 0xFF; //已经发生欠压
	}
	
	if(val1 == 0)	//没有发生欠压
	{
		Software_Counter_1ms.Undervoltage_Protection_Delay = 0;
	}
	
	if(val1 == 0xFF)	//已经发生欠压
	{
		Software_Counter_1ms.Undervoltage_Protection_Delay = 65535;
	}
	
	//if(g_AfeRegs.R0.bitmap.CUV)		//发生电池欠压
	if((val1 != 0) && (Software_Counter_1ms.Undervoltage_Protection_Delay > 15000)) //发生欠压并保持了15S
	{
		lock = 1;
		Flag.Undervoltage = 1;
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[4] = 9900;	//错误代码
		
		if(CHARGER == 0)	//没插入充电器，欠压保护关机
		{
			DSG_OFF;
			CHG_OFF;
			CHG_OFF;
			PDSG_OFF;
			PCHG_OFF;
			Flag.Power = 3;
		}
			
		
		for(i=0;i<AFE_MAX_CELL_CNT;i++)
		{
			if(DVC_1124.Single_Voltage[i] > 3000)
			{
				val2++;
			}
		}
		
		if(val2 == 0)	//所有电池电压均大于3.0V
		{
			Flag.Undervoltage = 0;
			lock = 0;
			Software_Counter_1ms.Undervoltage_Protection_Delay = 0;
			
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[4] = 0;	//错误代码
			
			r0 = g_AfeRegs.R0.cleanflag;
			clean_flag &= ~(1<<5);
			g_AfeRegs.R0.cleanflag = 0;
			
			while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
			{
				i++;
			}
			g_AfeRegs.R0.cleanflag = r0;
		}
	}
}

/**************************************************
 * @brie  :BMS_Discharge_Overcurrent_Protection()
 * @note  :放电过流保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Discharge_Overcurrent_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	
	//if(g_AfeRegs.R0.bitmap.OCD2)	//发生2级放电过流
	
	if(DVC_1124.Current_CC2 > 110)	//110A过流
	{
		Flag.Electric_Discharge_Overcurrent = 1;
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 9900;	//错误代码
		
		if(Software_Counter_1ms.Discharge_Overcurrent_Delay >= 1000)	//放电过流持续1S，关机
		{
			DSG_OFF;
			CHG_OFF;
			CHG_OFF;
			PDSG_OFF;
			PCHG_OFF;
			Flag.Power = 3;
		}
			
		r0 = g_AfeRegs.R0.cleanflag;
		clean_flag &= ~(1<<2);
		g_AfeRegs.R0.cleanflag = clean_flag;
		
		while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
		{
			i++;
		}
		g_AfeRegs.R0.cleanflag = r0;
		
	}	
	else
	{
		Flag.Electric_Discharge_Overcurrent = 0;
		Software_Counter_1ms.Discharge_Overcurrent_Delay = 0;
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 0;	//错误代码
	}
}

/**************************************************
 * @brie  :BMS_Charge_Overcurrent_Protection()
 * @note  :充电过流保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Charge_Overcurrent_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	static uint8_t lock = 0;
	
	//if(g_AfeRegs.R0.bitmap.OCC2)	//发生2级充电过流
	
	if(DVC_1124.Current_CC2 < -20)	//20A过流
	{
		Flag.Charging_Overcurrent = 1;
		CHARG_OFF;					//关闭充电器
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[6] = 9900;	//错误代码
		lock = 1;
		Software_Counter_1ms.Charge_Overcurrent_Delay = 0;
	}
	else if(DVC_1124.Current_CC2 > -1) //1A
	{
		if(lock == 1)
		{
			if(Software_Counter_1ms.Charge_Overcurrent_Delay > 10000)
			{
				lock = 0;
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[6] = 0;	//错误代码
				
				if((CHARGER == 1) && (Flag.Overvoltage == 0))	//充电器插入并且没有发生过压
				{
					if((Flag.Overtemperature == 0) && (Flag.Lowtemperature == 0))	//没有发生过温和低温
					{
						Flag.Charger_ON = 0;
					}
				}
				
				r0 = g_AfeRegs.R0.cleanflag;
				clean_flag &= ~(1<<1);
				g_AfeRegs.R0.cleanflag = clean_flag;
				
				while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
				{
					i++;
				}
				g_AfeRegs.R0.cleanflag = r0;
			}
		}
	}
}

/**************************************************
 * @brie  :BMS_Short_Circuit_Protection()
 * @note  :短路保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Short_Circuit_Protection(void)
{
	if(g_AfeRegs.R0.bitmap.SCD)		//发生放电短路
	{
		DSG_OFF;
		CHG_OFF;
		CHG_OFF;
		PDSG_OFF;
		PCHG_OFF;
		Flag.Power = 3;
		Flag.Short_Circuit = 1;
	}
}

/**************************************************
 * @brie  :BMS_Overtemperature_Protection()
 * @note  :过温保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Overtemperature_Protection(void)
{
	static uint8_t lock = 0;
	
	if(lock == 0)	//没发生过温
	{
		if( (DVC_1124.IC_Temp > 65.0f) ||
			(DVC_1124.GP3_Temp > 65.0f) ||
			(DVC_1124.GP1_Temp > 55.0f) ||
			(DVC_1124.GP4_Temp > 55.0f)
			) 
		{
			if(Software_Counter_1ms.Overtemperature_Protection_Delay >= 1000)	//过温延时1S
			{
				Flag.Overtemperature = 1;
				CHARG_OFF;					//关闭充电器
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[7] = 9900;	//错误代码
				lock = 1;
			}
		}
		else
		{
			Software_Counter_1ms.Overtemperature_Protection_Delay = 0;
		}
	}
	else	//已经发生过温
	{
		if( (DVC_1124.IC_Temp < 60.0f) &&
			(DVC_1124.GP3_Temp < 60.0f) &&
			(DVC_1124.GP1_Temp < 50.0f) &&
			(DVC_1124.GP4_Temp < 50.0f)
			) 
		{
			Software_Counter_1ms.Overtemperature_Protection_Delay = 0;
			Flag.Overtemperature = 0;
			lock = 0;
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[7] = 0;	//错误代码 T9
			
			if((CHARGER == 1) && (Flag.Overvoltage == 0) && (Flag.Charging_Overcurrent == 0))	//充电器插入并且没有发生过压 没有发生充电过流
			{
				if(Flag.Lowtemperature == 0)	//没有发生低温
				{
					Flag.Charger_ON = 0;
				}
			}
		}
	}
}

/**************************************************
 * @brie  :BMS_Low_Temperature_Protection()
 * @note  :低温保护
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Low_Temperature_Protection(void)
{
	static uint8_t lock = 0;
	
	if(lock == 0)	//没发生低温
	{
		if(CHARGER == 1)
		{
			if( (DVC_1124.GP1_Temp < 0) ||
				(DVC_1124.GP4_Temp < 0)		
				)
			{
				Flag.Lowtemperature = 1;
				CHARG_OFF;					//关闭充电器
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 9900;	//错误代码
				lock = 1;
			}
		}
		else
		{
			if( (DVC_1124.GP1_Temp < -20.0f) ||
				(DVC_1124.GP4_Temp < -20.0f)		
				)
			{
				Flag.Lowtemperature = 1;
				//没插入充电器没有动作
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 9900;	//错误代码
				lock = 1;
			}
		}
	}
	else //已经发生低温
	{
		if(CHARGER == 1)
		{
			if( (DVC_1124.GP1_Temp > 5.0f) ||
				(DVC_1124.GP4_Temp > 5.0f)		
				)
			{
				if((CHARGER == 1) && (Flag.Overvoltage == 0) && (Flag.Charging_Overcurrent == 0))	//充电器插入并且没有发生过压 没有发生充电过流
				{
					if((Flag.Overtemperature == 0))	//没有发生高温
					{
						Flag.Charger_ON = 0;
					}
				}
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 0;	//错误代码
				Flag.Lowtemperature = 0;
				lock = 0;
			}
		}
		else
		{
			if( (DVC_1124.GP1_Temp > -15.0f) ||
				(DVC_1124.GP4_Temp > -15.0f)		
				)
			{
				//没有动作
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 0;	//错误代码
				Flag.Lowtemperature = 0;
				lock = 0;
			}
		}
	}
}

//#define K1 -0.05f
//#define B1 1500
/**************************************************
 * @brie  :VESC_Cock_Head()
 * @note  :VESC翘头
 * @param :无
 * @retval:无
 **************************************************/
//void VESC_Cock_Head(void)
//{
//	static uint8_t lock = 0;
//	if(lock == 0)
//	{
//		if(Flag.Cock_Head == 1)	//需要翘头
//		{
//			if(VESC_CAN_RX_DATA.pSTATUS->Rpm > 0)
//			{
//				Set_PPM(1000);
//			}
//			else
//			{
//				Set_PPM(2000);
//			}
//			lock = 1;
//			Software_Counter_1ms.Cock_Head = 0;
//		}
//	}
//	else 
//	{
//		if(Flag.Cock_Head == 0)
//		{
//			lock = 0;
//			Set_PPM(1500);
//		}
//	}
//}
	
/**************************************************
 * @brie  :DVC1124_Abnormal()
 * @note  :DVC1124异常处理
 * @param :无
 * @retval:无
 **************************************************/
void BMS_Protection_Task(void)
{
	BMS_Overvoltage_Protection();			//过压保护		T5
	BMS_Undervoltage_Protection();			//欠压保护		T6
	BMS_Discharge_Overcurrent_Protection();	//放电过流保护	T7
	BMS_Charge_Overcurrent_Protection();	//充电过流保护	T8
	BMS_Short_Circuit_Protection();			//短路保护		
	BMS_Overtemperature_Protection();		//过温保护		T9
	BMS_Low_Temperature_Protection();		//低温保护		T10
	//VESC_Cock_Head();
}



