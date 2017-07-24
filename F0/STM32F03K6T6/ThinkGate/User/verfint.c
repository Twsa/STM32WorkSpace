#include "verfint.h"
extern ADC_HandleTypeDef hadc;

/*************************************************************************************
*  Function Name                    :    ADCVoltage
*  Create Date                      :    2017/07/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ����ADC��ȡ�豸�Ĳο���ѹ
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/24  Twsa Liu         None           None
**************************************************************************************/
void ADCVoltage(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
	
//	        (++) ADC conversion by polling:
//          (+++) Activate the ADC peripheral and start conversions
//                using function HAL_ADC_Start()
//          (+++) Wait for ADC conversion completion 
//                using function HAL_ADC_PollForConversion()
//          (+++) Retrieve conversion results 
//                using function HAL_ADC_GetValue()
//          (+++) Stop conversion and disable the ADC peripheral 
//                using function HAL_ADC_Stop()
	int index=0;
	uint32_t testBuf=0;
	
	//��ʼ����ADCת������
  HAL_ADC_Start(&hadc);
	
	for(index=0;index<10;index++)
	{
//		 HAL_ADC_Start_DMA(&hadc,testBuf,10);
		 testBuf=HAL_ADC_GetValue(&hadc);
     printf("%d\r\n",2*testBuf);
	}
	HAL_ADC_Stop(&hadc);
}
