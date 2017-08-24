#include "sys.h"

char count_reset=0;
void  Usart_str(char *RX_buffer)
{
  uint16_t i=0,status1=0,save=0;
	while(status1!=1)
	{
		count_reset=0;
		while((USART1->ISR & 0x0020)==0x0020)
		{		
			if (count_reset>=30)
			{
				 count_reset=0;
					save=i;
					if (save==0)
					break;

					status1=1;
						break; 
			}															
		}
		if((USART1->ISR & 0x0020)==0x0020)
		{	  
				if((USART1->ISR & 0x0020)!=0x0020) break;
				
				*(RX_buffer+i)=USART1->RDR;
				i++;
		}
  }
}

/*************************************************************************************
*  Function Name                    :    ReceiveTest
*  Create Date                      :    2017/07/26
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �������ݲ���  ���Գɹ�
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/26  Twsa Liu         None           None
*************************************************************************************/

void ReceiveTest(void)
{
	uint8_t testBuf=0;
	while(1)
	{
	  //�ȴ�RXNE set
	  while ((USART1->ISR & 0x0020)!=0x0020);
		//������ܵ�0xbb��ʼ��ֵ
		testBuf=USART1->RDR;
		printf("%c",testBuf);
	}
}

/*************************************************************************************
*  Function Name                    :    receiveBody
*  Create Date                      :    2017/07/26
*  Author/Corporation               :    Twsa Liu
*  Description                      :   
                                        
*  Param                            :    
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/26  Twsa Liu         None           None
*************************************************************************************/
uint8_t receiveStatus=0X00;
uint8_t receiveCommandBuf[17]={0};
uint8_t headerBuf[3]={0};
uint8_t bodyBuf[15]={0};
uint8_t endBuf[3]={0};

uint8_t bodyIndex=0;
uint8_t bodyCount=0;
//extern volatile uint32_t msTicks;                                 // counts 1ms timeTicks
uint32_t timeOut=0;

static uint8_t receiveBody(void)
{
	if(receiveStatus==0x01) return 0;
	
	while((USART1->ISR & 0x0020)!=0x0020);      //��ʾ�Ѿ���ʼ��������
	receiveStatus=0X01;
	bodyBuf[bodyIndex++]=USART1->RDR;
	
	while(bodyIndex<14)
	{		
		while ((USART1->ISR & 0x0020)!=0x0020);
		bodyBuf[bodyIndex++]=USART1->RDR;
	}
	
	bodyIndex=0;
//	memcpy (&endBuf,&bodyBuf[12],2);       
  
	printf("%s\n",bodyBuf);
	printf("%s\n",endBuf);
	return 0;	
}

static uint8_t receiveHeader(void)
{
	uint8_t i=0;
	uint8_t Connected=0;
	while(i<2)
	{
						//�ȴ�RXNE set
		while ((USART1->ISR & 0x0020)!=0x0020);
	
		//�ж�RDR���'b'���ߡ�B��
		if((USART1->RDR & 'B')=='B'||(USART1->RDR & 'b')=='b')
		{		
			headerBuf[i]=USART1->RDR;
			i++;
		}
		else
		{
			  Connected=USART1->RDR;
				i=0;
		}
	}
	 receiveStatus=0x00;
   	printf("%s\n",headerBuf);	
	return SUCCESS;
}

static uint8_t receiveEnd(void)
{
	uint8_t i=0;
	
	while(i<2)
	{
		//�ȴ�RXNE set
		while ((USART1->ISR & 0x0020)!=0x0020);
	
		//�ж�RDR���'b'���ߡ�B��
		if((USART1->RDR & '7')=='7')
		{		
			endBuf[i++]=USART1->RDR;
			
			while ((USART1->ISR & 0x0020)!=0x0020);
                               		
			if((USART1->RDR & 'E')!='E' && (USART1->RDR & 'e')!='e')
			{                                  //������7�ж���һ�������ǲ���e
				i=0;
//			  receiveBody();                //���յ��Ĳ���e
			}
			else
			{
			  endBuf[i++]=USART1->RDR;  
			}
		}
		else 
		{
		}
	}
   	printf("%s",endBuf);	
	return SUCCESS;
}


//void LockReceiveCommand(uint8_t *receiveBuf,uint8_t commandLength)
void LockReceiveCommand(void)
{
	
	while(1)                //�ⲿ��ѭ��
	{
		while(1)              //�ڲ�����ѭ��
		{
        if(receiveHeader()==SUCCESS)
				{
					 receiveBody();                //������ܵ�BB�Ϳ�ʼ����
				}
//			receiveEnd();
		}
	}
}

