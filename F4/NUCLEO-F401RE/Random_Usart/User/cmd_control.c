/*************************************************************************************
*  File Name                        :    rceive_handle.c
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �����µ��߳̽�������
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
	CmdBufInit(&CommCmdRxBuf, CommRxBuf, C_CommRxBufLen, 5, 1000);     //���ܵ����ݽṹ��ʼ��
	CmdBufInit(&CommCmdTxBuf, CommTxBuf, C_CommTxBufLen, 5, 30);     //�������ݵĽṹ��ʼ��
}

/*************************************************************************************
*  Function Name                    :  
*  Create Date                      :    2017/08/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ���յ���ȷ�����Ȼ����н���
                                        
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
	if(Packet_End_Flag)              //�������ݰ�β��ʾ
	{
		Packet_End_Flag =0;
		CmdStrToData(&CommCmdRxBuf);  //���ܵ�����ת��
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
*  Description                      :    ���������û�м��ܲ��֣�����ͷ��β�Լ�У��λ�ļ��
                                        
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
	if(Packet_End_Flag)              //�������ݰ�β��ʾ
	{
		Packet_End_Flag =0;
		CmdStrToData_Simple(&CommCmdRxBuf);  //���ܵ�����ת��
	}
//	CmdCheckData(&CommCmdRxBuf);
	if(CommCmdRxBuf.CmdOk)                 //���ݰ���ʽ���ɹ�
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
*  Description                      :    �Խ��ܵ����ݽ�������ƥ����֤
                                         ��ƥ��ɹ������ݽ��д���  ����RC4���ܵ����ݵ�����ͷ��β
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
	if(CommCmdRxBuf.CmdOk)          //û�����ݸ�ʽ���
	{
		CmdStrToData(&CommCmdRxBuf);  //���ܵ�����ת��
		
		//CommCmdHandle();
		CommCmdHandleNew();						//����������
		CommCmdRxBuf.CmdOk = 0;
		CommCmdRxBuf.DataPtr = 0;     //���ݽ�����ɣ��������
	}
	CmdRxOvertimeCheck(&CommCmdRxBuf);
}

static void CommCtrl_RandomSyntax_Simple(void)
{
	if(CommCmdRxBuf.CmdOk)          //û�����ݸ�ʽ���
	{
		CmdStrToData_Simple(&CommCmdRxBuf);  //���ܵ�����ת��
		
		CommCmdHandleNew();						//����������
		CommCmdRxBuf.CmdOk = 0;
		CommCmdRxBuf.DataPtr = 0;     //���ݽ�����ɣ��������
	}
	CmdRxOvertimeCheck(&CommCmdRxBuf);
}
/*************************************************************************************
*  Function Name                    :    DataReceiveSyntaxHandle
*  Create Date                      :    2017/09/01
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �������ݸ�ʽ��ѡ�񣬲����ڰ�����Ӧ�Ľ��մ�����

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
* Description: 	��ӱ������ݵ�ѡ��ģʽ
*/
void DataReceiveSyntaxHandle(const uint8_t modeSelected)
{
	CMD_BUF *cmdPtrTmp = &CommCmdRxBuf;
	cmdPtrTmp->Mode = modeSelected;
  switch(modeSelected)
	{
		case 0x01:CommCtrl();           		     break;        //���ܵ����ݸ�ʽ��ͷ��β��RC4����
		case 0x02:CommCtrl_Simple();   				   break;        //���ܵ����ݸ�ʽ��ͷ��β����RC4����
		case 0x03:CommCtrl_RandomSyntax();     	 break;  			 //���ܵ����ݸ�ʽ������ͷ��βRC4����
		case 0x04:CommCtrl_RandomSyntax_Simple();break; 			 //���ܵ����ݸ�ʽ������ͷ��β������RC4����
		default:break;
	}
	CommCmdHandleNew();
}
