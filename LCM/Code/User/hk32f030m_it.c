/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hk32f030m_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************

  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "hk32f030m_it.h"
#include "hk32f030m.h"
#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "vesc_uasrt.h"
#include "buzzer.h"
#include "test.h"
#include "flag_bit.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
	/* USER CODE BEGIN W1_HardFault_IRQn 0 */
	/* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
#ifdef ADV2
		LED_Counter++;
#endif
		WS2812_Counter++;
#ifdef USE_BUZZER
		Buzzer_Time++;
#endif
		Charge_Time++;
		Flashlight_Time++;
		Usart_Time++;
		ADC_Time++;
		Shutdown_Time_S++;
		Flashlight_Detection_Time++;
		Charger_Detection_1ms++;

		// 16bit counters overflow quickly, don't let them:
		if (Power_Time < 30000)
			Power_Time++;
		if (Idle_Time < 30000)
			Idle_Time++;
		
		KEY1_Scan();
#ifdef USE_BUZZER
		Buzzer_Scan();
#endif
  }
}

void USART1_IRQHandler(void)
{
	static uint8_t count = 0;
	
	if((USART1->ISR & USART_ISR_RXNE) != 0)	//Receiving interruption
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
		if (count < sizeof(VESC_RX_Buff)) {
			// all messages should be shorter than 80 bytes but you never know...
			VESC_RX_Buff[count++] = USART1->RDR; //Send the received data into the receiving buffer
		}
		else
		{
			// The message is too long, just do a dummy read
			volatile uint8_t dummy = USART1->RDR;
		}
	}
	if((USART1->ISR & USART_ISR_IDLE) != 0) //Idle interruption
	{
		count = 0; //After one frame of data is received, the count is cleared to zero
		VESC_RX_Flag = 1; //Set flag position 1
		USART_ClearFlag(USART1,USART_ISR_IDLE);
		USART_ReceiveData(USART1);
	}
	if((USART1->ISR & USART_ISR_ORE) != 0)  //Overflow
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);
		USART_ReceiveData(USART1);
	}
}


/******************************************************************************/
/* hk32f030m Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_hk32f030m.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT HKMicroChip *****END OF FILE****/
