/*************************************************************************************
*  File Name                        :    power_control.c
*  Create Date                      :    2017/08/31
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �͹��Ĵ�����,��Ϊ���͹���ģʽ
*************************************************************************************/

/*
* Private Includes
*/
#include "power_control.h"

/*************************************************************************************
*  Function Name                    :    StopMode_Control
*  Create Date                      :    2017/08/31
*  Author/Corporation               :    Twsa Liu
*  Description                      :    Stop ģʽ������
                                        
*  Param                            :    modeSelected:ѡ��Stopģʽ��0x01:WFI,0x02:WFE
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/31  Twsa Liu         None           None
*************************************************************************************/
void StopMode_Control(const uint8_t modeSelected)
{
	HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON,modeSelected);
}

/*************************************************************************************
*  Function Name                    :    SleepMode_Control
*  Create Date                      :    2017/08/31
*  Author/Corporation               :    Twsa Liu
*  Description                      :    Stop ģʽ������
                                        
*  Param                            :    modeSelected:ѡ������ģʽ��0x01:WFI,0x02:WFE
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/31  Twsa Liu         None           None
*************************************************************************************/
//void SleepMode_Control(const uint8_t modeSelected)
//{
//	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, modeSelected);
//}
