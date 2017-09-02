#include "sys.h"
#include "Serial.h"

/***查看时钟的配置信息****/
uint32_t SysClockFreq=0;             
uint32_t HCLKFreq=0;
uint32_t PCLK1Freq=0;
uint32_t PCLK2Freq=0;
RCC_OscInitTypeDef  GetOscConfigStruct={0};
RCC_ClkInitTypeDef  GetClockConfigStruct={0};
uint32_t *pFLatency=0;
void View_Clock(void)
{
	SysClockFreq=HAL_RCC_GetSysClockFreq ();
	HCLKFreq=HAL_RCC_GetHCLKFreq();
	PCLK1Freq=HAL_RCC_GetPCLK1Freq();
	PCLK2Freq=HAL_RCC_GetPCLK2Freq();
//	HAL_RCC_GetOscConfig(&GetOscConfigStruct);
	printf("SysClockFreq: %d\r\n",SysClockFreq);
	printf("HCLKFreq: %d\r\n",HCLKFreq);
	printf("PCLK1Freq: %d\r\n",PCLK1Freq);
	printf("PCLK2Freq: %d\r\n",PCLK2Freq);
}
