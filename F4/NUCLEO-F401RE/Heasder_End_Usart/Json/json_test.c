#include <stdio.h>
#include "sys.h"
#include "json_test.h"
#include "cJSON.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart2;

void JasonTest(void)
{

		cJSON *root=NULL,*item=NULL; 
	  char *out=NULL;
		root=cJSON_CreateObject();             //创建验证对象结构体
		cJSON_AddItemToObject(root,"coordinate",item=cJSON_CreateObject());	
	
	 cJSON_AddStringToObject(item,"X","1");
//	 cJSON_AddStringToObject(item,"Y","1");
	
		cJSON_AddStringToObject(root,"flag","16");	
	  out=cJSON_PrintUnformatted(root);	
	  cJSON_Delete(root);	free(out);
		
}

void CoordinateTest(void)
{
	printf("v1=123\r\n");
	HAL_Delay(200);
}



