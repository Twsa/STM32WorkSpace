#ifndef __DATA_STRUCT_H_
#define __DATA_STRUCT_H_
/*--------Includes----------*/
#include "sys.h"

/*---------�궨��------------*/
#define MAXSIZE 		  80  //���Ա�洢�ռ�ĳ�ʼ����ֵ
#define LISTINCREMENT 10	//���Ա�洢�ռ�ķ�������
#define LIST_INIT_SIZE 100
/*---------ָʾ״̬----------*/
typedef enum
{
  OVERFLOW=0x00,
  OK=0X01,
	ERR=0X02
} Status;

/*-----���Ա�����Ľṹ��-----*/
typedef unsigned char ElemType;
typedef struct
{
	ElemType *elem;   			//�洢�ռ����ַ
	uint32_t length;        //��ǰ����
	uint32_t listsize; 			//��ǰ����Ĵ洢��������(sizeof(ElemType))��Ϊ��λ
}SqList;									//˳���

/*----------��������----------*/
void InitList_Sq_Test(void);
void ListInsert_Sq_Test(void);
void ListDelete_Sq_Test(void);

Status InitList_Sq(SqList *List);
void Create_Sq(SqList *List);
Status Merge(SqList La , SqList Lb , SqList *Lc);

#endif
