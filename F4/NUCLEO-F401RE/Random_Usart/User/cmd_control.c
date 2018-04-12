/*************************************************************************************
*  File Name                        :    rceive_handle.c
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    开启新的线程接受数据
*************************************************************************************/
/* USER CODE BEGIN Includes */
#include "sys.h"
#include "cmd_control.h"
#include "receive_handle.h"
/* USER CODE END Includes */

#define	CommCom				COM1
#define	C_CommRxBufLen		256
#define	C_CommTxBufLen		128
#define	C_PartTotal				30

/* External variables --------------------------------------------------------*/
extern CMD_BUF cmdBuf[C_CmdBufTotal];

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t CommRxBuf[C_CommRxBufLen];
uint8_t CommTxBuf[C_CommTxBufLen];
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */




/*************************************************************************************
*  Function Name                    :   
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
void CommCtrlInit()
{
	CmnCmdInit();
	//1,2 30 ;3,4 0xffff
	CmdBufInit(&CommCmdRxBuf, CommRxBuf, C_CommRxBufLen, 5, 1000);     //接受的数据结构初始化
	CmdBufInit(&CommCmdTxBuf, CommTxBuf, C_CommTxBufLen, 5, 30);     //发送数据的结构初始化
}

/*************************************************************************************
*  Function Name                    :  
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    接收到正确的命令，然后进行解析
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/ 
extern UART_HandleTypeDef huart2;
void CommCmdHandleNew()
{
	uint8_t *test="Hello World";
	uint8_t flagCom=0x01;
	flagCom=StrCompare(test,&CommCmdRxBuf.Buf[1],11);
	if(flagCom==0)
		printf("Good Boy!\r\n");
//		HAL_UART_Transmit(&huart2,&CommCmdRxBuf.Buf[1],12,100);
	
}
/*************************************************************************************
*  Function Name                    :  
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :   
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
extern uint8_t  Packet_End_Flag;
static void CommCtrl(void)
{
	if(Packet_End_Flag)              //接受数据包尾提示
	{
		Packet_End_Flag =0;
		CmdStrToData(&CommCmdRxBuf);  //接受的数据转换
	}
//	CmdCheckData(&CommCmdRxBuf);
	if(CommCmdRxBuf.CmdOk)
	{
		//CommCmdHandle();
		CommCmdHandleNew();
		CommCmdRxBuf.CmdOk = 0;
		CommCmdRxBuf.DataPtr = 0;
	}
	CmdRxOvertimeCheck(&CommCmdRxBuf);
}

/*************************************************************************************
*  Function Name                    :    CommCtrl_Simple
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    接受命令部分没有加密部分；含包头包尾以及校验位的检测
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/08/24  Twsa Liu         None           None
*************************************************************************************/
static void CommCtrl_Simple(void)
{
	if(Packet_End_Flag)              //接受数据包尾提示
	{
		Packet_End_Flag =0;
		CmdStrToData_Simple(&CommCmdRxBuf);  //接受的数据转换
	}
//	CmdCheckData(&CommCmdRxBuf);
	if(CommCmdRxBuf.CmdOk)                 //数据包格式检查成功
	{
		//CommCmdHandle();
		CommCmdHandleNew();
		CommCmdRxBuf.CmdOk = 0;
		CommCmdRxBuf.DataPtr = 0;
	}
	CmdRxOvertimeCheck(&CommCmdRxBuf);
}

/*************************************************************************************
*  Function Name                    :    CommCtrl_RandomSyntax
*  Create Date                      :    2017/09/01
*  Author/Corporation               :    Twsa Liu
*  Description                      :    对接受的数据进行数据匹配验证
                                         对匹配成功的数据进行处理  进行RC4加密的数据但不包头包尾
*  Param                            :    None
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/01  Twsa Liu         None           None
*************************************************************************************/
static void CommCtrl_RandomSyntax(void)
{
	
//	 if( (cmdPtrTmp->Mode == _RxMode_RC4_NoEndHeader) || (cmdPtrTmp->Mode == _RxMode_NoEndHeader))
//		 if(cmdPtrTmp->DataPtr>0)
//			 CommCmdRxBuf.CmdOk=1;
		 
//	CmdCheckData(&CommCmdRxBuf);
	if(CommCmdRxBuf.CmdOk)          //没有数据格式检查
	{
		CmdStrToData(&CommCmdRxBuf);  //接受的数据转换
		
		//CommCmdHandle();
		CommCmdHandleNew();						//命令处理服务函数
		CommCmdRxBuf.CmdOk = 0;
		CommCmdRxBuf.DataPtr = 0;     //数据接受完成，缓存清空
	}
	CmdRxOvertimeCheck(&CommCmdRxBuf);
}

static void CommCtrl_RandomSyntax_Simple(void)
{
	if(CommCmdRxBuf.CmdOk)          //没有数据格式检查
	{
		CmdStrToData_Simple(&CommCmdRxBuf);  //接受的数据转换
		
		CommCmdHandleNew();						//命令处理服务函数
		CommCmdRxBuf.CmdOk = 0;
		CommCmdRxBuf.DataPtr = 0;     //数据接受完成，缓存清空
	}
	CmdRxOvertimeCheck(&CommCmdRxBuf);
}
/*************************************************************************************
*  Function Name                    :    DataReceiveSyntaxHandle
*  Create Date                      :    2017/09/01
*  Author/Corporation               :    Twsa Liu
*  Description                      :    接受数据格式的选择，并在内包含相应的接收处理方法

*  Param                            :    None
*  Return Code                      :    
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/01  Twsa Liu         None           None
*************************************************************************************/
/*
* Date:					2017/09/02
* RevisedBy:		Twsa Liu
* Description: 	添加保存数据的选择模式
*/
void DataReceiveSyntaxHandle(const uint8_t modeSelected)
{
	CMD_BUF *cmdPtrTmp = &CommCmdRxBuf;
	cmdPtrTmp->Mode = modeSelected;
  switch(modeSelected)
	{
		case 0x01:CommCtrl();           		     break;        //接受的数据格式包头包尾带RC4加密
		case 0x02:CommCtrl_Simple();   				   break;        //接受的数据格式包头包尾不带RC4加密
		case 0x03:CommCtrl_RandomSyntax();     	 break;  			 //接受的数据格式不带包头包尾RC4加密
		case 0x04:CommCtrl_RandomSyntax_Simple();break; 			 //接受的数据格式不带包头包尾，不带RC4加密
		default:break;
	}
	CommCmdHandleNew();
}
