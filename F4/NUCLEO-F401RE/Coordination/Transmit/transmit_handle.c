/*************************************************************************************
*  File Name                    :    transmit_handle.c
*  Create Date                      :    2017/08/13
*  Author/Corporation               :    Twsa Liu
*  Description                      :    开启新的线程发送数据
*************************************************************************************/

/* USER CODE BEGIN Includes */
#include "sys.h"
#include "transmit_handle.h"
#include <cmsis_os.h>
#include "Board_Buttons.h"
#include "Board_LED.h"
/* USER CODE END Includes */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t *transmitTestBuf = (uint8_t *)"v1=200.0\r\n";

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void transmit_thread(void const *argument);
void button_thread(void const *argument);
/* USER CODE END PFP */

/*----------------------------------------------------------------------------
 Define the thread handles and thread parameters
 *---------------------------------------------------------------------------*/
osThreadId transmit_ID , button_ID;	
osThreadDef(transmit_thread, osPriorityNormal, 1, 250);
osThreadDef(button_thread, osPriorityNormal, 1, 250);

/*************************************************************************************
*  Struct Name                      :    TransmitStruct
*  Create Date                      :    2017/08/13
*  Author/Corporation               :    Twsa Liu
*  Description                      :    传入到发送发送线程的的参数结构
                                        
*  Param                            :    
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/13  Twsa Liu         None           None
*************************************************************************************/
typedef struct
{
	const uint8_t *stringSource;
	const uint32_t length;
}TransmitStruct;

/*************************************************************************************
*  Function Name                    :    transmit_thread
*  Create Date                      :    2017/08/13
*  Author/Corporation               :    Twsa Liu
*  Description                      :    发送数据的线程的方法
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/13  Twsa Liu         None           None
*************************************************************************************/

void transmit_thread(void const *argument)
{
	static uint32_t count=0;
	for (;;)
	{
//		osSignalWait(0x01,osWaitForever); 
//		osSignalSet(transmit_ID,0x01);
    if(Buttons_GetState()==1)          //检测到按键按下
		{
			count++;
			osDelay(1);                      //延时1ms
			
			if(count>=33 && count<=666)
			{
				if(Buttons_GetState()==0)      //检测到按键弹起
				{
					count=0;
				  printf("%s",transmitTestBuf);
				}
			}
		  else if(count>=666)
			{ 
				 printf("%s",transmitTestBuf);
			}
		}
   else		
	 {
		 count=0;                          //如果按键没有按下，消抖时间初始化
	 }
	}
}

/*************************************************************************************
*  Function Name                    :    button_thread
*  Create Date                      :    2017/08/13
*  Author/Corporation               :    Twsa Liu
*  Description                      :    线程检测按键的跳变沿来产生发送数据的信号
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/13  Twsa Liu         None           None
*************************************************************************************/
void button_thread(void const *argument)
{
	for (;;)
	{
    if(Buttons_GetState()==1)       //检测到按键按下
		{
//			 osSignalSet(transmit_ID,0x01);
			 HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
			 osDelay(1000);
		}
	}
}
/*************************************************************************************
*  Function Name                    :    TransmitStr
*  Create Date                      :    2017/08/13
*  Author/Corporation               :    Twsa Liu
*  Description                      :    发送数据的方法
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/13  Twsa Liu         None           None
*************************************************************************************/
void TransmitStr(void)
{
	transmit_ID = osThreadCreate(osThread(transmit_thread), NULL);
	button_ID = osThreadCreate(osThread(button_thread), NULL);

	osKernelStart ();                         // start thread execution
	
	for (;;);
}
