/*************************************************************************************
*  File Name                        :    linear_list.c
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ���Ա�Ĳ���������ʵ�ַ���
*************************************************************************************/
/*----------Includes------------*/
#include "data_struct.h"
#include "stdlib.h"
/*----------�ⲿ����-----------*/
extern UART_HandleTypeDef huart2;

/*************************************************************************************
*  Function Name                    :    InitList_Sq
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ����һ���յ����Ա�
                                        
*  Param                            :   
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/03  Twsa Liu         None           None
*************************************************************************************/
/*
* ����
* ���Խ��������ͨ��
* ���Խ���
*/
Status InitList_Sq(SqList *List)
{
	List->elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));  //����洢�ռ�
	if(!List->elem) return(OVERFLOW);    	  //�洢�ռ����ʧ��
	
	List->length=0;                         //Ԫ�ظ���Ϊ��
	List->listsize = LIST_INIT_SIZE;        //��ǰ����Ĵ洢����
	return OK;
}

uint8_t status;
SqList List;
void InitList_Sq_Test(void)
{
  status=InitList_Sq(&List);
}

/*************************************************************************************
*  Function Name                    :    ListInsert_Sq
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ���Ѿ����������Ա��в���Ԫ��
																				 ��˳���List�ĵ�i��Ԫ��֮ǰ�����µ�Ԫ�ص�e,i�ĺϷ���ΧΪ
																					1<=i<=List.length+1
                                        
*  Param                            :    Sqlist *List:�Ѿ����������Ա�Ķ�ָ�룻
																				 int i:������ElemType e:��Ҫ�����Ԫ��
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/03  Twsa Liu         None           None
*************************************************************************************/
/*
* ����
* ���Խ�����ڳ�ʼ��List�в������ݳɹ���
* 					�������ݵ�List�в������ݳɹ�;
*						�ڲ��������ǲ���λ��֮����������Ƴɹ�
* ���Խ���
*/
Status ListInsert_Sq(SqList *List,uint32_t i,ElemType e)
{
	if(i<1 || i>List->length+1) return ERR;  				//����λ�ò��Ϸ�
	if(List->length >= List->listsize)              //��ǰ�洢�ռ����������ӷ���
	{
		ElemType *newbase = (ElemType *)realloc(List->elem,
		(List->listsize+LISTINCREMENT) * sizeof(ElemType));//�������ӿռ�
		
		if(!newbase) return(OVERFLOW);  								//�洢�ռ����ʧ��
		List->elem = newbase;													//�µĻ���ַ
		List->listsize+=LISTINCREMENT;								//���Ӵ洢����
	}
	
	ElemType *q = &(List->elem[i-1]);          			//qָʾ�����λ��
	for(ElemType *p=&(List->elem[List->length-1]);p>=q;--p)
		*(p+1) = *p; 																	//����λ�ü�֮���Ԫ������
	
	*q=e;																						//����e
	++List->length;																	//����1
	return OK;
}

void ListInsert_Sq_Test(void)
{
	for(int i=1;i<5;i++)
	status=ListInsert_Sq(&List,i,i);
	
  status=ListInsert_Sq(&List,3,0x60);
}
/*************************************************************************************
*  Function Name                    :    Create_Sq
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ����һ������Ҫ����õ�Ϊ
																				n:��ĳ��ȣ����е�����
                                        
*  Param                            :    Sqlist *List:�Ѿ����������Ա�Ķ�ָ�룻

*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/03  Twsa Liu         None           None
*************************************************************************************/
void Create_Sq(SqList *List)
{
	uint8_t i,n;
//	printf("Create a sorted list\r\n");
//	printf("the number of list's elements:");
	
	while( (USART2->SR & 0x0020)!=0x0020);
		n=USART2->DR;
	
	for(i=0;i<n;i++)
	{
//		printf("the %d is:",i+1);		
	  while( (USART2->SR & 0x0020)!=0x0020);
		List->elem[i]=USART2->DR;
//		printf("\n");
	}
}

/*************************************************************************************
*  Function Name                    :    ListDelete_Sq
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    ���Ѿ����������Ա���ɾ��Ԫ��
																				 ��˳���List�ĵ�i��Ԫ��֮ǰ�����µ�Ԫ�ص�e,i�ĺϷ���ΧΪ
																					1<=i<=List.length+1
                                        
*  Param                            :    Sqlist *List:�Ѿ����������Ա�Ķ�ָ�룻
																				 int i:������ElemType e:��Ҫ�����Ԫ��
*  Return Code                      :    None
																			
*  Global Variable                  :    w
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/03  Twsa Liu         None           None
*************************************************************************************/
Status ListDelete_Sq(SqList *List ,uint32_t i, ElemType *e)
{
	if((i<1) || (i>List->length)) return ERR;	//ɾ����λ�ò��Ϸ�
	
	ElemType *p=&(List->elem[i-1]);    				//pΪ��ɾ��Ԫ�ص�λ��
	*e = *p;                                  //��ɾ����Ԫ�ص�ֵ���Ƹ�e
	ElemType *q = List->elem + List->length-1;//��βԪ�ص�λ��
	for(++p;p<=q;p++)  *(p-1) = *p; 					//��ɾ��Ԫ��֮���Ԫ������
  --List->length;                     			//����1
	return OK;
}

/*
* ����;ɾ��������Ԫ��
* ���Խ��������ͨ��
* ���Խ���
*/
ElemType e;
void ListDelete_Sq_Test(void)
{
  status=ListDelete_Sq(&List,3,&e);
}

/*************************************************************************************
*  Function Name                    :    Merge
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    �ϳ�����˳���,����С�����˳������
                                        
*  Param                            :   
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/03  Twsa Liu         None           None
*************************************************************************************/
Status Merge(SqList La , SqList Lb , SqList *Lc)
{
	ElemType *pa,*pb,*pc,*pa_last,*pb_last;
	
	pa=La.elem;pb=Lb.elem;             //�����Ļ���ַ
	Lc->listsize=Lc->length=La.length+Lb.length;
	pc=Lc->elem=(ElemType *)malloc(Lc->listsize * sizeof(ElemType));
	
	if(!Lc->elem) return(OVERFLOW);
	pa_last=La.elem + La.length-1;     //�����β�ĵ�ַ
	pb_last=Lb.elem + Lb.length-1;
	
	while(pa<=pa_last && pb<=pb_last)           
	{
		if(*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	
	while(pa<=pa_last) *pc++ = *pa++;
	while(pa<=pb_last) *pc++ = *pb++;
	return OK;
}
