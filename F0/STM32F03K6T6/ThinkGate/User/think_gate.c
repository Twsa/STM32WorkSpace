#include "think_gate.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include "arc4.h"

/*************************************************************************************
*  Function Name                    :    SaveKey
*  Create Date                      :    2017/07/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �����ʼ����Կ�ͻỰ��Կ
                                        
*  Param                            :    uint8_t *initializationKey,uint32_t initializationKeyLen,
	           uint8_t * communicationKey,uint32_t communicationKeyLen
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/24  Twsa Liu         None           None
*************************************************************************************/
uint8_t InitializationKey[9]="12345678";
uint8_t CommunicationKey[9]="abcdefgh";

void SaveKey(uint32_t keyAddressForKey,uint8_t *initializationKey,uint32_t initializationKeyLen,
	           uint8_t * communicationKey,uint32_t communicationKeyLen)
{
  uint8_t * KeyBuf =(uint8_t *)malloc(initializationKeyLen+communicationKeyLen-1);
	memcpy (KeyBuf,initializationKey,initializationKeyLen-1);  //0:1  ;1:2   //2:1 ;2:3
	memcpy (KeyBuf+initializationKeyLen-1,communicationKey,communicationKeyLen-1);
	*(KeyBuf+initializationKeyLen+communicationKeyLen-2)='\0';
	
	
  FlashWrite(keyAddressForKey,KeyBuf,initializationKeyLen+communicationKeyLen-1);
	
	free(KeyBuf);   //�ͷ���ʱ�ڴ�
}

/*************************************************************************************
*  Function Name                    :    GetKey
*  Create Date                      :    2017/07/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ��ȡ��Կ
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/24  Twsa Liu         None           None
*************************************************************************************/
keyGet theKeyIGet={0};
keyGet GetKey(const uint32_t keyAddressForKey,const uint32_t initializationKeyLen,const uint32_t communicationKeyLen)
{
//	FlashRead(KEY_ADDRESS,sizeof(InitializationKey)+sizeof(CommunicationKey)-1);
	uint32_t keyLength=initializationKeyLen+communicationKeyLen;
	uint8_t *testBuf=(uint8_t *) malloc(keyLength);
	
	memcpy (testBuf,(uint32_t *)keyAddressForKey,keyLength-1);  //0:1  ;1:2   //2:1 ;2:3	
	testBuf[keyLength-2]='\0';
	
	memcpy (theKeyIGet.keyInit,testBuf,initializationKeyLen-1);  //0:1  ;1:2   //2:1 ;2:3
	memcpy (theKeyIGet.keyCommun,testBuf+initializationKeyLen-1,communicationKeyLen-1);
	
	free(testBuf);
	return theKeyIGet;
}


/*************************************************************************************
*  Function Name                    :    MotorControl
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ����Ŀ���
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
//#define CLOSED 0x01
//#define OPENED 0X02


//uint8_t doorStatus=0x01;     //Ĭ���ŵ�״̬���ǹرյ�

void MotorControl(void)
{
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);   //������
	
	HAL_Delay(500);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	
//  HAL_Delay(1000);
//	
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
}

/*************************************************************************************
*  Function Name                    :    SendFacilityInfo
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ���ͻ�ȡ���豸����Ϣ
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
#include "str_hex.h"

#define MCUID_ADDRESS_BASE  0x1FFFF7AC
extern UART_HandleTypeDef huart1;

static uint8_t MyCopy(uint8_t *destAddress,uint8_t *sourceAddress,uint32_t length)
{
	uint32_t len=length;
	
	while(len<length)
	{
		*(destAddress+len)=*(sourceAddress+len);
		len++;
	}
	return 0;
}
static uint8_t lockRandomOpenDoor[5]="c0c1";

void SendFacilityInfo(void)
{	
	uint8_t lockInfo[LOCKINFO_LENGTH]={0};
	uint8_t lockInfoStr[55]={0};
	uint8_t lockRandomCrypt[8]={0};
	uint8_t temp16[2]={0};
	uint8_t lockRandomPlain[4]={0};
	
	//��ȡ���ı�ʶ��
  uint32_t mcuID[3];

	//��ȡCPUΨһID 12���ֽ�
	mcuID[0]=*(uint32_t *)(MCUID_ADDRESS_BASE);
	mcuID[1]=*(uint32_t *)(MCUID_ADDRESS_BASE+4);
	mcuID[2]=*(uint32_t *)(MCUID_ADDRESS_BASE+8);

//	printf("ID:%x%x%x\r\n",mcuID[0],mcuID[1],mcuID[2]);
	
	//��ȡ���İ汾�� 2���ֽ�
	uint16_t lockVersion=0;
	
	lockVersion=Lock_GetVersion();
//	printf("Version:%x\r\n",lockVersion);
	
	//��ȡ���� 2���ֽ�
	uint16_t lockVoltage=0;
	
	lockVoltage=ADCVoltage();
//	printf("lockVoltage:%d\r\n",lockVoltage);
	
	//�������ʱ��λ0x0000;
	uint16_t randomNum=0xc0c1;
	

	
	//������Ϣ����
	lockInfo[0]=0xbb; //��Ϣͷ
	lockInfo[1]=0x01; //֡����
	lockInfo[2]=0x01; //ָ�����
	
	uint16_t ParamLength=0x0012;  //ָ���������
	temp16[0]=ParamLength>>8;
	temp16[1]=(uint8_t)ParamLength;	
	memcpy (&lockInfo[3],&temp16,2);  
	
  memcpy (&lockInfo[5],(uint8_t *)mcuID,12);   //������ı�ʶ��
	
	temp16[0]=lockVersion>>8;
	temp16[1]=(uint8_t)lockVersion;	
	memcpy (&lockInfo[17],&temp16,2);       //������İ汾��
	
	temp16[0]=lockVoltage>>8;
	temp16[1]=(uint8_t)lockVoltage;	
	memcpy (&lockInfo[19],&temp16,2);       //��ӵ���
	

	
	temp16[0]=randomNum>>8;
	temp16[1]=(uint8_t)randomNum;	
	memcpy (&lockInfo[21],&temp16,2);         //��������
	
	Hex2Str(lockRandomPlain,temp16,sizeof(temp16));	
	memcpy (lockRandomOpenDoor,lockRandomPlain,4);
  //��ʼ����Կ����
	Arc4Crypt(lockRandomPlain,4);
	Hex2Str(lockRandomCrypt,lockRandomPlain,sizeof(lockRandomPlain));
	
	uint32_t i=1;
	uint16_t checkAndEnd=0;
	//����У��λ
	while(i<23)
	{
		checkAndEnd+=lockInfo[i];
		i++;
	}

	temp16[0]=(uint8_t)checkAndEnd;
	temp16[1]=0x7e;         //��ӽ�β��ʶ
	memcpy (&lockInfo[25],&temp16,2);         //��������
//	HAL_UART_Transmit(&huart1,lockInfo,sizeof(lockInfo),0xff);  //Hex��ʽ����
	
	//Hexת��ΪStr����ʽ
  Hex2Str(lockInfoStr,lockInfo,sizeof(lockInfo));
	memcpy (&lockInfoStr[42],&lockRandomCrypt,8);         //��������
  
	
//��ʼ����Կ����
	
	HAL_UART_Transmit(&huart1,lockInfoStr,sizeof(lockInfoStr)-1,0xff);
//	Arc4Crypt(lockInfo,LOCKINFO_LENGTH);
//	HAL_UART_Transmit(&huart1,lockInfo,LOCKINFO_LENGTH,0xff);
	
}


/*************************************************************************************
*  Function Name                    :    GetInfo
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ��ȡ������
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
uint8_t getCommandBuf[COMMAND_LENGTH]={0};
uint8_t hexPlain[(COMMAND_LENGTH-4)/2]={0};
//uint8_t CommandForOpenTest[COMMAND_LENGTH]="bb8bc309e63981ee93940b69fc935c6d9042ae7e";
//lockRandom  bb00020004d8c35ae5007e

uint8_t GetInfo(void)
{
	uint32_t hexLength=(COMMAND_LENGTH-4)/2; 
  uint32_t strLength=(COMMAND_LENGTH-4); 	
	uint8_t InfoUsed[COMMAND_LENGTH-5]={0};
	uint8_t lockRandomTemp8[8]={0};
	uint8_t lockRandomTemp4[5]={0};
	
	uint8_t commandBuf[2]={0}; 
	commandInfo command={0};
	
//  if(HAL_UART_Receive_IT(&huart1,getCommandBuf,sizeof(getCommandBuf)-1)==HAL_OK)
//	{
		
		memcpy (InfoUsed,&getCommandBuf[2],strLength);      
//		printf("\r\n");
		
		Str2Hex(InfoUsed ,hexPlain,sizeof(InfoUsed));
		Arc4Decrypt(hexPlain,hexLength,(uint8_t *)"12345678");
//		HAL_UART_Transmit(&huart1,InfoUsed,sizeof(InfoUsed),0xff); 
//  	HAL_UART_Transmit(&huart1,hexPlain,sizeof(hexPlain),0xff); 
	
		memcpy (commandBuf,&hexPlain[2],2); 	
		command.Command=(uint8_t )atoi((char *)commandBuf);
	
		if(command.Command==0x01) 
		{
			return 0x01; 
		}
	  else if(command.Command==0x02)
		{
			memcpy (lockRandomTemp8,&hexPlain[8],8); 
//			  	HAL_UART_Transmit(&huart1,lockRandomTemp8,sizeof(lockRandomTemp8),0xff); 
			Str2Hex(lockRandomTemp8 ,lockRandomTemp4,8);
			Arc4Decrypt(lockRandomTemp4,4,(uint8_t *)"abcdefgh");
			
			if(strcmp((char *)lockRandomTemp4,(char *)lockRandomOpenDoor)==0)
			{
				return 0x02;
			}			
			else
				return 0xff;
		}
		else
			return 0xff;
//	  printf("%x",command.Command);

//	}
}

/*************************************************************************************
*  Function Name                    :    Arc4Decrypt
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    Arc4����
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
void Arc4Decrypt(uint8_t *textBuf, uint32_t strLength,uint8_t *key)
{
		arc4_context ctx;
	  arc4_setup( &ctx, (uint8_t *)key, 8 );
    arc4_crypt( &ctx,textBuf , strLength);
	
//	  Str2Hex(textBuf ,hexPlain,COMMAND_LENGTH);	
}


/*************************************************************************************
*  Function Name                    :    Arc4Crypt
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    Arc4j����
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
void Arc4Crypt(uint8_t *textBuf,uint32_t hexLength)
{
		arc4_context ctx;
	  arc4_setup( &ctx, (uint8_t *)InitializationKey, 8 );
    arc4_crypt( &ctx,textBuf , hexLength);
}

/*************************************************************************************
*  Function Name                    :    BleConnected
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    Ble �����ϵ���ʾ�����Լ������߻��ߡ�����
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
uint8_t ConnectedBuf[10]={0};
uint8_t BleConnectedCheck(void)
{
	
	if(HAL_UART_Receive_IT(&huart1,ConnectedBuf,sizeof(ConnectedBuf)-1)==HAL_OK)
	{
		HAL_UART_Transmit(&huart1,ConnectedBuf,sizeof(ConnectedBuf)-1,0xff); 
	}
	return 0;
}

/*************************************************************************************
*  Function Name                    :    MsgHandle
*  Create Date                      :    2017/07/25
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ��Ϣ�������
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/25  Twsa Liu         None           None
*************************************************************************************/
void MsgHandle(void)
{
	 uint8_t handleFlag=0xff;
	
	handleFlag=GetInfo();
	switch(handleFlag)
	{
		case GET_LOCK_INFO:SendFacilityInfo();break;
		case OPEN_LOCK:MotorControl();break; 
		default:break;
	};	
}


/*************************************************************************************
*  Function Name                    :    Arc4Test
*  Create Date                      :    2017/07/26
*  Author/Corporation               :    Twsa Liu
*  Description                      :    Arc4����
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/26  Twsa Liu         None           None
*************************************************************************************/

void Arc4Test(void)
{
	  uint8_t textCiper[]={0x8b,0xc3,0x09,0xe5,0x39,0x81,0xee,0x96,0xc0,0x03,0x3a,0xfd};
		
	  uint8_t textPlain[]="abcsefgh";
		
		arc4_context ctx;
	  arc4_setup( &ctx, (uint8_t *)"12345678", 8 );
    arc4_crypt( &ctx,textCiper , sizeof(textCiper));
	
		HAL_UART_Transmit(&huart1,textCiper,sizeof(textCiper),0xff);
}
