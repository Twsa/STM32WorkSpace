#ifndef __SYS_H_
#define __SYS_H_
//#define HAL_ADC_MODULE_ENABLED

#include "stm32f0xx.h"
#include "Serial.h"

//需要线程开发的需要开此项
#ifdef __THEAD_MANAHE_H_
  #include "thread_manage.h"
#endif


uint32_t BSP_GetVersion(void);
 void Error_Handler(void);
 void SystemCoreClockConfigure(void);
void SystemClock_Config(void);
void View_Clock(void);
extern void HAL_RCC_CSSCallback(void);
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void GPIO_Config(void);
void View_GPIO(void);
void DelayMs (uint32_t dlyTicks);
//void DMA_Config(void);
#endif

