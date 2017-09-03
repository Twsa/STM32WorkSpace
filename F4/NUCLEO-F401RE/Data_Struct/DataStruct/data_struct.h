#ifndef __DATA_STRUCT_H_
#define __DATA_STRUCT_H_
/*--------Includes----------*/
#include "sys.h"

/*---------宏定义------------*/
#define MAXSIZE 		  80  //线性表存储空间的初始分配值
#define LISTINCREMENT 10	//线性表存储空间的分配增量
#define LIST_INIT_SIZE 100
/*---------指示状态----------*/
typedef enum
{
  OVERFLOW=0x00,
  OK=0X01,
	ERR=0X02
} Status;

/*-----线性表操作的结构体-----*/
typedef unsigned char ElemType;
typedef struct
{
	ElemType *elem;   			//存储空间基地址
	uint32_t length;        //当前长度
	uint32_t listsize; 			//当前分配的存储容量（以(sizeof(ElemType))）为单位
}SqList;									//顺序表

/*----------函数声明----------*/
void InitList_Sq_Test(void);
void ListInsert_Sq_Test(void);
void ListDelete_Sq_Test(void);

Status InitList_Sq(SqList *List);
void Create_Sq(SqList *List);
Status Merge(SqList La , SqList Lb , SqList *Lc);

#endif
