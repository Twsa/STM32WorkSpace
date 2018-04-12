/*************************************************************************************
*  File Name                        :    rceive_handle.c
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    开启新的线程接受数据
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
	系统节拍定时器服务回调函数
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
*  Description                      :    接受数据的方法
                                        
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
*  Description                      :    设定时间的线程
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void time_thread(void const *argument)   //该线程应该等到接收到数据启动
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
*  Description                      :    两个字符比较函数
                                        
*  Param                            :    str1:比较的字符1的指针，str2:比较的字符2的指针
																				 length:比较的长度
*  Return Code                      :    0：一致；1：不一致
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* 测试部分
uint8_t state=0xff;
uint8_t test1[5]="1234";
uint8_t test2[5]="1234";
uint8_t test3[5]="1111";
uint8_t test4[5]="4444";

state=StrCompare(test1,test2,4);
state=StrCompare(test1,test3,4);
state=StrCompare(test1,test2,4);
state=StrCompare(test1,test4,4);
* 测试通过
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
*  Description                      :    复制一个字符数组到另一个字符数组中中
                                        
*  Param                            :    destStr:复制到目标的字符的指针，srcStr:复制的字符的源数组的指针
																				 length:复制字符串的部分的长度
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* 测试部分
uint8_t test1[5]="1234";
uint8_t test2[5]={0};

StrCopy(test2,test1,5);
* 测试通过
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
*  Description                      :    命令缓存区初始化
                                        
*  Param                            :    cmdPtr:命令结构体的指针；cmdStrBuf:命令字符的指针；
                                         bufLength:缓冲区的长度；
                                         errorsMax:最大错误次数；overTime:超时检测的预设时间；
*  Return Code                      :    SUCCESS:初始化成功；ERROR;初始化失败
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* 测试
uint8_t status = 0;
CMD_BUF test ={0};
uint8_t test1[5]="1234";

status = CmdBufInit( &test ,test1,4,5,1000);
* 测试通过
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
*  Description                      :    计算校验位
                                        
*  Param                            :    addrSrc:需要计算的数据的源地址；packetLength:数据包的长度
*  Return Code                      :    返回计算得到的校验位
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* 测试
uint8_t test[4]={0x01,0x02,0x03,0x04};
uint32_t sum=0;

sum=GetCheckSum(test,4);
* 测试通过
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
*  Description                      :    装配发送的数据结构
                                        
*  Param                            :    cmdPtr:命令结构体的指针；cmdType:命令类型；cmdCode:命令代码
																				 paramBuf:参数缓存区；paramLength:命令参数长度；
*  Return Code                      :    返回数据的长度
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
/*
* 测试
	uint32_t len=0;
	CMD_BUF test;
	uint8_t ack=0x01;
	uint8_t cmd =0x01;
	uint8_t buf[1]={0x01};

  len=AssembleCmd2Send_Hex(&test,ack,cmd,buf,1);		
	HAL_UART_Transmit(&huart2,test.Buf,len,0xff);	
* 测试通过
*/
uint32_t AssembleCmd2Send_Hex(CMD_BUF* cmdPtr, const uint8_t cmdType, const uint8_t cmdCode, 
                     const uint8_t* paramBuf, const uint16_t paramLength)
{
	uint32_t i;
	uint8_t checkSum=0;
	cmdPtr->Buf=(uint8_t *)(cmdPtr-1);   //添加外部地址
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
	cmdPtr->Buf[5+paramLength]= checkSum;              //加入校验位
	cmdPtr->Buf[6+paramLength]=Packet_End;
	cmdPtr->DataLen = paramLength+7;
	cmdPtr->DataPtr = 0;
	return cmdPtr->DataLen;
}

//参数含义同上，是上面的功能的精简版,只有发送参数，没有校验位，头尾等
/*
* 测试
CMD_BUF test={0};
uint32_t len=0;
len= AssembleCmd2SendSimple_Hex(&test,"1234",4);
* 测试通过
*/
uint32_t AssembleCmd2SendSimple_Hex
(CMD_BUF *cmdPtr,const uint8_t* paramBuf, const uint16_t paramLength)
{
	uint16_t i = 0;
	//uint8_t cs = 0;
	cmdPtr->Buf=(uint8_t *)paramBuf;      //缓存区指针设置
	
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
*  Description                      :    保存接收到的数据，简单的版本
                                        
*  Param                            :    cmdPtr:命令结构体的指针；data:接收到的数据
*  Return Code                      :    SUCCESS:保存data成功；ERROR:保存data失败
																			
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
*  Description                      :    保存接收到的data
                                        
*  Param                            :    cmdPtr:命令结构体的指针；data:接收到的数据
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
	if(cmdPtr->DataPtr==0)                   //还没开始接收到数据
	{
		if(data==Packet_Header)            //接受到数据包头
		{
			cmdPtr->Buf[0] = data;
			cmdPtr->DataPtr++;
		}
	}
	else if(cmdPtr->DataPtr==1)             //接受到一个数据，该数据就是数据包头
	{
		if(data!=Packet_Header)           //接受到的数据不是数据包头
		{
			cmdPtr->Buf[cmdPtr->DataPtr++] = data;   //保存数据
		}
	}                               
	else if(cmdPtr->DataPtr<cmdPtr->BufLen)    
	{
		cmdPtr->Buf[cmdPtr->DataPtr++] = data;
	}
	return 0;
}

//上面的方法的精简版
uint8_t CmdSaveByteSimple(CMD_BUF* cmdStr, uint8_t data)
{
	if(cmdStr->DataPtr<cmdStr->BufLen)
	{
		cmdStr->Buf[cmdStr->DataPtr++] = data;
		return 0;
	}
	return 1;
}

//最终需要确定保存的数据，需要考虑包尾
uint8_t CmdSaveStr(CMD_BUF* cmdPtr, uint8_t data)
{
	cmdPtr->Time = cmdPtr->OverTime;          //开始接受数据时就加载超时检测的时间
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
			Packet_End_Flag = 1;                       //接受到数据包包尾
		}
	}
	return 0;
}

/*************************************************************************************
*  Function Name                    :    CmdCheckData
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    检查接受到的或者发送的数据格式是否正确
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
			if(cmdPtr->DataLen>(C_CMD_RX_BUF_LEN-7))        //检查数据的长度是否超过预设长度
			{
				cmdPtr->DataPtr =0;     
			}
			else if(cmdPtr->DataPtr>=(cmdPtr->DataLen+7))   //检查数据包包尾
			{
				data = cmdPtr->Buf[cmdPtr->DataLen+6];
				if(data==Packet_End)                          //检查包尾成功
				{
					                                            //check packet    检查校验位
					if(cmdPtr->Buf[cmdPtr->DataLen+5]==GetCheckSum(&cmdPtr->Buf[1], cmdPtr->DataLen+4))
					{
						cmdPtr->CmdOk = 1;                        //指令代码格式是正确的
						cmdPtr->CmdType = cmdPtr->Buf[1];    
						cmdPtr->Cmd = cmdPtr->Buf[2];
						return;
					}
					else
					{
						cmdPtr->DataPtr =0;        //校验位错误              
						//BleSendRCK((uint8_t*)DATA_CheckSUM_Error,sizeof(DATA_CheckSUM_Error));
					}
				}
				else
				{
					cmdPtr->DataPtr =0;          //检查包尾错误，数据指针引导清空
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
                             
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
                                        
*  Param                            :    cmdPtr:命令结构体的指针；
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
	
	if(InfoLength%2==0)//说明长度偶数，正确
	{
		memcpy (InfoUsed,&cmdPtr->Buf[1],InfoLength);      
		
		Str2Hex(InfoUsed ,StrPlain,InfoLength);
		Arc4Decrypt(StrPlain,InfoLength>>1,AllKey);   //公钥解密负载数据
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
	else //有效长度为奇数，数据错误
	{
		
	}


}

void CmdStrToData_Simple(CMD_BUF* cmdPtr)
{
	uint16_t InfoLength;
	InfoLength	= cmdPtr->DataPtr - 2; 
	uint8_t InfoUsed[100]={0};
	
	if(InfoLength%2==0)//说明长度偶数，正确
	{
		memcpy (InfoUsed,&cmdPtr->Buf[1],InfoLength);      
		
//		Str2Hex(InfoUsed ,StrPlain,InfoLength);

		cmdPtr->Buf[0] = Packet_Header;
		Str2Hex(InfoUsed ,HexPlain,InfoLength);
		memcpy(&cmdPtr->Buf[1],HexPlain,InfoLength);
		cmdPtr->Buf[(InfoLength/2)+1] = Packet_End;
		CmdCheckData(&CommCmdRxBuf);

	}
	else //有效长度为奇数，数据错误
	{
		
	}
}
