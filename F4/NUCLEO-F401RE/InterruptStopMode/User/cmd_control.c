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
	CmdBufInit(&CommCmdRxBuf, CommRxBuf, C_CommRxBufLen, 5, 30);     //接受的数据结构初始化
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
void CommCmdHandleNew()
{
	;
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
void CommCtrl(void)
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
void CommCtrl_Simple(void)
{
	if(Packet_End_Flag)              //接受数据包尾提示
	{
		Packet_End_Flag =0;
		CmdStrToData_Simple(&CommCmdRxBuf);  //接受的数据转换
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
