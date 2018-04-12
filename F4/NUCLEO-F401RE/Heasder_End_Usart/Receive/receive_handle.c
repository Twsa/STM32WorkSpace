/*************************************************************************************
*  File Name                        :    rceive_handle.c
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �����µ��߳̽�������
*************************************************************************************/

/* USER CODE BEGIN Includes */
#include "sys.h"
#include "receive_handle.h"
#include "string.h"
#include "str_hex.h"
#include "cmd_control.h"
/* USER CODE END Includes */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
CMD_BUF* CmdBufList[C_CmdBufTotal];
uint8_t CmdBufTotal = 0;
uint8_t Packet_End_Flag=0;
CMD_BUF cmdBuf[C_CmdBufTotal];
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/*----------------------------------------------------------------------------*/


void CmnCmdInit(void)
{
	CmdBufTotal = 0;
}

/*
	ϵͳ���Ķ�ʱ������ص�����
*/
void HAL_SYSTICK_Callback(void)
{
  	CmdTimeCtrl();
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

//  /* USER CODE END USART2_IRQn 0 */
//  HAL_UART_IRQHandler(&huart2);

  /* USER CODE BEGIN USART2_IRQn 1 */
	 uint8_t dataBuf=0;
		while ((USART2->SR & 0x0020)!=0x0020);
		dataBuf=USART2->DR;
		CmdSaveStr(&CommCmdRxBuf,dataBuf);	
  /* USER CODE END USART2_IRQn 1 */
}
/*************************************************************************************
*  Function Name                    :    ReceiveStr
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �������ݵķ���
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void ReceiveStr(void)
{

	
	for (;;);
}

/*************************************************************************************
*  Function Name                    :    time_thread
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �趨ʱ����߳�
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void time_thread(void const *argument)   //���߳�Ӧ�õȵ����յ���������
{
	for(;;)
	{
//    osDelay(1);
		CmdTimeCtrl();                         
	}
}

/*************************************************************************************
*  Function Name                    :    StrCompare
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �����ַ��ȽϺ���
                                        
*  Param                            :    str1:�Ƚϵ��ַ�1��ָ�룬str2:�Ƚϵ��ַ�2��ָ��
																				 length:�Ƚϵĳ���
*  Return Code                      :    0��һ�£�1����һ��
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* ���Բ���
uint8_t state=0xff;
uint8_t test1[5]="1234";
uint8_t test2[5]="1234";
uint8_t test3[5]="1111";
uint8_t test4[5]="4444";

state=StrCompare(test1,test2,4);
state=StrCompare(test1,test3,4);
state=StrCompare(test1,test2,4);
state=StrCompare(test1,test4,4);
* ����ͨ��
*/
uint8_t StrCompare(const uint8_t *str1 , const uint8_t *str2 , const uint32_t length)
{
	uint8_t i=0;
	
  while(i<length)
  {
  	if(str1[i]!=str2[i])
  		return 1;
  	i++;
  }
  return 0;
}
/*************************************************************************************
*  Function Name                    :    StrCopy
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ����һ���ַ����鵽��һ���ַ���������
                                        
*  Param                            :    destStr:���Ƶ�Ŀ����ַ���ָ�룬srcStr:���Ƶ��ַ���Դ�����ָ��
																				 length:�����ַ����Ĳ��ֵĳ���
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* ���Բ���
uint8_t test1[5]="1234";
uint8_t test2[5]={0};

StrCopy(test2,test1,5);
* ����ͨ��
*/
void StrCopy(uint8_t *destStr , const uint8_t *srcStr , const uint32_t length)
{
	uint32_t lengthTmp = length;
	while(lengthTmp--) *destStr++ = *srcStr++;
}

/*************************************************************************************
*  Function Name                    :    CmdBufInit
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ���������ʼ��
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻cmdStrBuf:�����ַ���ָ�룻
                                         bufLength:�������ĳ��ȣ�
                                         errorsMax:�����������overTime:��ʱ����Ԥ��ʱ�䣻
*  Return Code                      :    SUCCESS:��ʼ���ɹ���ERROR;��ʼ��ʧ��
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* ����
uint8_t status = 0;
CMD_BUF test ={0};
uint8_t test1[5]="1234";

status = CmdBufInit( &test ,test1,4,5,1000);
* ����ͨ��
*/
uint8_t CmdBufInit(CMD_BUF *cmdPtr , uint8_t *cmdStrBuf , const uint32_t bufLength
	                 ,const uint32_t errorsMax , const uint32_t overTime)
{
	if(CmdBufTotal<C_CmdBufTotal)
	{
		cmdPtr->Buf = cmdStrBuf;
		cmdPtr->BufLen = bufLength;
		cmdPtr->DataPtr = 0;
		cmdPtr->DataLen = 0;
		cmdPtr->OverTime = overTime;
		cmdPtr->Time = 0;
		cmdPtr->CmdOk = 0;
		cmdPtr->HaveNewData = 0;
		cmdPtr->ErrCount = 0;
		cmdPtr->ErrMax = errorsMax;	
		
		CmdBufList[CmdBufTotal++] = cmdPtr;
		return SUCCESS;
	}
	return ERROR;
}


/*************************************************************************************
*  Function Name                    :    GetCheckSum
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ����У��λ
                                        
*  Param                            :    addrSrc:��Ҫ��������ݵ�Դ��ַ��packetLength:���ݰ��ĳ���
*  Return Code                      :    ���ؼ���õ���У��λ
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* ����
uint8_t test[4]={0x01,0x02,0x03,0x04};
uint32_t sum=0;

sum=GetCheckSum(test,4);
* ����ͨ��
*/
uint32_t GetCheckSum(volatile uint8_t *addrSrc , const uint32_t packetLength)
{
	uint32_t i;
	uint32_t sum=0;
	for (i=0;i<packetLength;i++)  
	{
		sum += addrSrc[i];
	}	
	return sum;
}

/*************************************************************************************
*  Function Name                    :    AssembleCmd2Send_Hex
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    װ�䷢�͵����ݽṹ
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻cmdType:�������ͣ�cmdCode:�������
																				 paramBuf:������������paramLength:����������ȣ�
*  Return Code                      :    �������ݵĳ���
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* ����
	uint32_t len=0;
	CMD_BUF test;
	uint8_t ack=0x01;
	uint8_t cmd =0x01;
	uint8_t buf[1]={0x01};

  len=AssembleCmd2Send_Hex(&test,ack,cmd,buf,1);		
	HAL_UART_Transmit(&huart2,test.Buf,len,0xff);	
* ����ͨ��
*/
uint32_t AssembleCmd2Send_Hex(CMD_BUF* cmdPtr, const uint8_t cmdType, const uint8_t cmdCode, 
                     const uint8_t* paramBuf, const uint16_t paramLength)
{
	uint32_t i;
	uint8_t checkSum=0;
	cmdPtr->Buf=(uint8_t *)(cmdPtr-1);   //����ⲿ��ַ
	cmdPtr->Buf[0]=Packet_Header;
 	cmdPtr->Buf[1]=cmdType;
	cmdPtr->Buf[2]=cmdCode;
	cmdPtr->Buf[3]=(uint8_t)(paramLength>>8);
	cmdPtr->Buf[4]=(uint8_t)paramLength;
	checkSum += cmdPtr->Buf[1];
	checkSum += cmdPtr->Buf[2];
	checkSum += cmdPtr->Buf[3];
	checkSum += cmdPtr->Buf[4];
	if(paramLength>0)
	{
		for (i=0;i<paramLength;i++)
		{
			cmdPtr->Buf[5+i]=paramBuf[i];
			checkSum += paramBuf[i];
		}
	}
	cmdPtr->Buf[5+paramLength]= checkSum;              //����У��λ
	cmdPtr->Buf[6+paramLength]=Packet_End;
	cmdPtr->DataLen = paramLength+7;
	cmdPtr->DataPtr = 0;
	return cmdPtr->DataLen;
}

//��������ͬ�ϣ�������Ĺ��ܵľ����,ֻ�з��Ͳ�����û��У��λ��ͷβ��
/*
* ����
CMD_BUF test={0};
uint32_t len=0;
len= AssembleCmd2SendSimple_Hex(&test,"1234",4);
* ����ͨ��
*/
uint32_t AssembleCmd2SendSimple_Hex
(CMD_BUF *cmdPtr,const uint8_t* paramBuf, const uint16_t paramLength)
{
	uint16_t i = 0;
	//uint8_t cs = 0;
	cmdPtr->Buf=(uint8_t *)paramBuf;      //������ָ������
	
	if(paramLength>0 && paramLength<=cmdPtr->BufLen)
	{
		for (i=0;i<paramLength;i++)
		{
			cmdPtr->Buf[i]=paramBuf[i];
		}
	}
	if(i>0)
	{
		if(cmdPtr->Buf[i-1]==0)
		{
			i--;
		}
	}
	cmdPtr->DataLen = i;
	cmdPtr->DataPtr = 0;
	return i;
}
/*************************************************************************************
*  Function Name                    :    CmdSaveByteSimple
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ������յ������ݣ��򵥵İ汾
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻data:���յ�������
*  Return Code                      :    SUCCESS:����data�ɹ���ERROR:����dataʧ��
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/



/*************************************************************************************
*  Function Name                    :    CmdSaveByteSimple
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ������յ���data
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻data:���յ�������
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
uint8_t CmdSaveByte(CMD_BUF* cmdPtr, uint8_t data)
{
	cmdPtr->Time = cmdPtr->OverTime;
	if(cmdPtr->CmdOk)return 1;
	cmdPtr->HaveNewData = 1;
	if(cmdPtr->DataPtr==0)                   //��û��ʼ���յ�����
	{
		if(data==Packet_Header)            //���ܵ����ݰ�ͷ
		{
			cmdPtr->Buf[0] = data;
			cmdPtr->DataPtr++;
		}
	}
	else if(cmdPtr->DataPtr==1)             //���ܵ�һ�����ݣ������ݾ������ݰ�ͷ
	{
		if(data!=Packet_Header)           //���ܵ������ݲ������ݰ�ͷ
		{
			cmdPtr->Buf[cmdPtr->DataPtr++] = data;   //��������
		}
	}                               
	else if(cmdPtr->DataPtr<cmdPtr->BufLen)    
	{
		cmdPtr->Buf[cmdPtr->DataPtr++] = data;
	}
	return 0;
}

//����ķ����ľ����
uint8_t CmdSaveByteSimple(CMD_BUF* cmdStr, uint8_t data)
{
	if(cmdStr->DataPtr<cmdStr->BufLen)
	{
		cmdStr->Buf[cmdStr->DataPtr++] = data;
		return 0;
	}
	return 1;
}

//������Ҫȷ����������ݣ���Ҫ���ǰ�β
uint8_t CmdSaveStr(CMD_BUF* cmdPtr, uint8_t data)
{
	cmdPtr->Time = cmdPtr->OverTime;          //��ʼ��������ʱ�ͼ��س�ʱ����ʱ��
	if(cmdPtr->CmdOk)return 1;
	cmdPtr->HaveNewData = 1;
	if(cmdPtr->DataPtr==0)
	{
		if(data==Packet_Header)
		{
			cmdPtr->Buf[0] = data;
			cmdPtr->DataPtr++;
		}
	}
	else if(cmdPtr->DataPtr==1)
	{
		if(data!=Packet_Header)
		{
			cmdPtr->Buf[cmdPtr->DataPtr++] = data;
		}
	}
	else if(cmdPtr->DataPtr<cmdPtr->BufLen)
	{
		if(data != Packet_End)
			cmdPtr->Buf[cmdPtr->DataPtr++] = data;
		else
		{
			cmdPtr->Buf[cmdPtr->DataPtr++] = data;
			Packet_End_Flag = 1;                       //���ܵ����ݰ���β
		}
	}
	return 0;
}

/*************************************************************************************
*  Function Name                    :    CmdCheckData
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �����ܵ��Ļ��߷��͵����ݸ�ʽ�Ƿ���ȷ
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void CmdCheckData(CMD_BUF* cmdPtr)
{
	uint16_t ti1;
	uint8_t data;
	if(cmdPtr->CmdOk==0)
	{
		if((cmdPtr->DataPtr>=7))
		{
			//cmdPtr->DataLen = ((cmdPtr->Buf[3])<<8)+((cmdPtr->Buf[4])&0xff);
			ti1 = cmdPtr->Buf[3];
			ti1<<=8;
			ti1 += cmdPtr->Buf[4];
			cmdPtr->DataLen = ti1;
			if(cmdPtr->DataLen>(C_CMD_RX_BUF_LEN-7))        //������ݵĳ����Ƿ񳬹�Ԥ�賤��
			{
				cmdPtr->DataPtr =0;     
			}
			else if(cmdPtr->DataPtr>=(cmdPtr->DataLen+7))   //������ݰ���β
			{
				data = cmdPtr->Buf[cmdPtr->DataLen+6];
				if(data==Packet_End)                          //����β�ɹ�
				{
					                                            //check packet    ���У��λ
					if(cmdPtr->Buf[cmdPtr->DataLen+5]==GetCheckSum(&cmdPtr->Buf[1], cmdPtr->DataLen+4))
					{
						cmdPtr->CmdOk = 1;                        //ָ������ʽ����ȷ��
						cmdPtr->CmdType = cmdPtr->Buf[1];    
						cmdPtr->Cmd = cmdPtr->Buf[2];
						return;
					}
					else
					{
						cmdPtr->DataPtr =0;        //У��λ����              
						//BleSendRCK((uint8_t*)DATA_CheckSUM_Error,sizeof(DATA_CheckSUM_Error));
					}
				}
				else
				{
					cmdPtr->DataPtr =0;          //����β��������ָ���������
				}
			}
		}
		else
		{
			
		}
	}
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :   	
                             
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void ErrInc(CMD_BUF* cmdPtr)
{
	if(cmdPtr->ErrMax==0)
	{
		cmdPtr->ErrMax = 10;
	}
	if(cmdPtr->ErrCount<cmdPtr->ErrMax)
	{
		cmdPtr->ErrCount++;
	}
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
uint8_t CmdCheckErrCount(CMD_BUF* cmdPtr)
{
	if(cmdPtr->ErrCount>=cmdPtr->ErrMax)
	{
		return 1;
	}
	return 0;
}


/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void CmdTimeCtrl(void)
{
	uint8_t tc1;
	for(tc1=0;tc1<CmdBufTotal;tc1++)
	{
		if(CmdBufList[tc1]->Time>0)
		{
			CmdBufList[tc1]->Time--;
		}
	}
}
/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
uint8_t CmdCheckTime(CMD_BUF* cmdPtr)
{
	if(cmdPtr->Time==0)
	{
		return 1;
	}
	return 0;
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void ErrMaxSet(CMD_BUF* cmdPtr, uint8_t ErrMax)
{
	cmdPtr->ErrMax = ErrMax;
}
/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void OverTimeSet(CMD_BUF* cmdPtr, uint16_t OverTime)
{
	cmdPtr->OverTime = OverTime;
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void CmdRxOvertimeCheck(CMD_BUF* cmdPtr)
{
	if(cmdPtr->DataPtr>0)
	{
		if(cmdPtr->Time==0)
		{
			cmdPtr->DataPtr = 0;
		}
	}
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void CmdResetOverTime(CMD_BUF* cmdPtr)
{
	cmdPtr->Time = cmdPtr->OverTime;
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
uint8_t CmdBufGetTxByte(CMD_BUF* cmdPtr, uint8_t* data)
{
	if(cmdPtr->DataLen<cmdPtr->BufLen&&cmdPtr->DataPtr<cmdPtr->DataLen)
	{
		*data = cmdPtr->Buf[cmdPtr->DataPtr++];
		return 0;
	}
	return 1;
}

/*************************************************************************************
*  Function Name                    :    
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    cmdPtr:����ṹ���ָ�룻
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
#include "arc4.h"
uint8_t StrPlain[100]={0};
uint8_t HexPlain[100]={0};
uint8_t AllKey[8] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
void CmdStrToData(CMD_BUF* cmdPtr)
{
	uint16_t InfoLength;
	InfoLength	= cmdPtr->DataPtr - 2; 
	uint8_t InfoUsed[100]={0};
//	uint8_t lockRandomTemp8[8]={0};
//	uint8_t lockRandomTemp4[5]={0};	
//	uint8_t commandBuf[2]={0}; 
//	commandInfo command={0};
	
	if(InfoLength%2==0)//˵������ż������ȷ
	{
		memcpy (InfoUsed,&cmdPtr->Buf[1],InfoLength);      
		
		Str2Hex(InfoUsed ,StrPlain,InfoLength);
		Arc4Decrypt(StrPlain,InfoLength>>1,AllKey);   //��Կ���ܸ�������
//		HAL_UART_Transmit(&huart1,InfoUsed,sizeof(InfoUsed),0xff); 
//  	HAL_UART_Transmit(&huart1,hexPlain,sizeof(hexPlain),0xff); 
		cmdPtr->Buf[0] = Packet_Header;
		Str2Hex(StrPlain ,HexPlain,InfoLength>>1);
		memcpy(&cmdPtr->Buf[1],HexPlain,(InfoLength>>2));
		cmdPtr->Buf[(InfoLength>>2)+1] = Packet_End;
		CmdCheckData(&CommCmdRxBuf);
//		memcpy (commandBuf,&hexPlain[2],2); 	
//		command.Command=(uint8_t )atoi((char *)commandBuf);
//	
//		if(command.Command==0x01) 
//		{
//			return 0x01; 
//		}
//	  else if(command.Command==0x02)
//		{
//			memcpy (lockRandomTemp8,&hexPlain[8],8); 
////			  	HAL_UART_Transmit(&huart1,lockRandomTemp8,sizeof(lockRandomTemp8),0xff); 
//			Str2Hex(lockRandomTemp8 ,lockRandomTemp4,8);
//			Arc4Decrypt(lockRandomTemp4,4,(uint8_t *)"abcdefgh");
//			
//			if(strcmp((char *)lockRandomTemp4,(char *)lockRandomOpenDoor)==0)
//			{
//				return 0x02;
//			}			
//			else
//				return 0xff;
//		}
//		else
//			return 0xff;
	}
	else //��Ч����Ϊ���������ݴ���
	{
		
	}


}

void CmdStrToData_Simple(CMD_BUF* cmdPtr)
{
	uint16_t InfoLength;
	InfoLength	= cmdPtr->DataPtr - 2; 
	uint8_t InfoUsed[100]={0};
	
	if(InfoLength%2==0)//˵������ż������ȷ
	{
		memcpy (InfoUsed,&cmdPtr->Buf[1],InfoLength);      
		
//		Str2Hex(InfoUsed ,StrPlain,InfoLength);

		cmdPtr->Buf[0] = Packet_Header;
		Str2Hex(InfoUsed ,HexPlain,InfoLength);
		memcpy(&cmdPtr->Buf[1],HexPlain,InfoLength);
		cmdPtr->Buf[(InfoLength/2)+1] = Packet_End;
		CmdCheckData(&CommCmdRxBuf);

	}
	else //��Ч����Ϊ���������ݴ���
	{
		
	}
}
