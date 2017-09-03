/*************************************************************************************
*  File Name                        :    linear_list.c
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    线性表的操作函数的实现方法
*************************************************************************************/
/*----------Includes------------*/
#include "data_struct.h"
#include "stdlib.h"
/*----------外部变量-----------*/
extern UART_HandleTypeDef huart2;

/*************************************************************************************
*  Function Name                    :    InitList_Sq
*  Create Date                      :    2017/09/03
*  Author/Corporation               :    Twsa Liu
*  Description                      :    构造一个空的线性表
                                        
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
* 测试
* 测试结果：测试通过
* 测试结束
*/
Status InitList_Sq(SqList *List)
{
	List->elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));  //申请存储空间
	if(!List->elem) return(OVERFLOW);    	  //存储空间分配失败
	
	List->length=0;                         //元素个数为零
	List->listsize = LIST_INIT_SIZE;        //当前分配的存储容量
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
*  Description                      :    在已经构建的线性表中插入元素
																				 在顺序表List的第i个元素之前插入新的元素的e,i的合法范围为
																					1<=i<=List.length+1
                                        
*  Param                            :    Sqlist *List:已经建立的线性表的额指针；
																				 int i:索引；ElemType e:需要插入的元素
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/09/03  Twsa Liu         None           None
*************************************************************************************/
/*
* 测试
* 测试结果：在初始化List中插入数据成功；
* 					在有数据的List中插入数据成功;
*						在插入数据是插入位置之后的数据右移成功
* 测试结束
*/
Status ListInsert_Sq(SqList *List,uint32_t i,ElemType e)
{
	if(i<1 || i>List->length+1) return ERR;  				//插入位置不合法
	if(List->length >= List->listsize)              //当前存储空间已满，增加分配
	{
		ElemType *newbase = (ElemType *)realloc(List->elem,
		(List->listsize+LISTINCREMENT) * sizeof(ElemType));//申请增加空间
		
		if(!newbase) return(OVERFLOW);  								//存储空间分配失败
		List->elem = newbase;													//新的基地址
		List->listsize+=LISTINCREMENT;								//增加存储容量
	}
	
	ElemType *q = &(List->elem[i-1]);          			//q指示插入的位置
	for(ElemType *p=&(List->elem[List->length-1]);p>=q;--p)
		*(p+1) = *p; 																	//插入位置及之后的元素右移
	
	*q=e;																						//插入e
	++List->length;																	//表长增1
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
*  Description                      :    创建一个表，需要输入得到为
																				n:表的长度；表中的数据
                                        
*  Param                            :    Sqlist *List:已经建立的线性表的额指针；

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
*  Description                      :    在已经构建的线性表中删除元素
																				 在顺序表List的第i个元素之前插入新的元素的e,i的合法范围为
																					1<=i<=List.length+1
                                        
*  Param                            :    Sqlist *List:已经建立的线性表的额指针；
																				 int i:索引；ElemType e:需要插入的元素
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
	if((i<1) || (i>List->length)) return ERR;	//删除的位置不合法
	
	ElemType *p=&(List->elem[i-1]);    				//p为被删除元素的位置
	*e = *p;                                  //被删除的元素的值复制给e
	ElemType *q = List->elem + List->length-1;//表尾元素的位置
	for(++p;p<=q;p++)  *(p-1) = *p; 					//被删除元素之后的元素左移
  --List->length;                     			//表长减1
	return OK;
}

/*
* 测试;删除第三个元素
* 测试结果：测试通过
* 测试结束
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
*  Description                      :    合成两个顺序表,按从小到大的顺序排列
                                        
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
	
	pa=La.elem;pb=Lb.elem;             //保存表的基地址
	Lc->listsize=Lc->length=La.length+Lb.length;
	pc=Lc->elem=(ElemType *)malloc(Lc->listsize * sizeof(ElemType));
	
	if(!Lc->elem) return(OVERFLOW);
	pa_last=La.elem + La.length-1;     //保存表尾的地址
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
