#ifndef _RECEIVE_HANDLE_H_
#include "sys.h"

typedef struct
{
	uint8_t* Buf;
	uint32_t BufLen;
	uint32_t DataPtr;
	uint32_t DataLen;
	uint32_t OverTime;
	uint32_t Time;
	uint8_t CmdType;
	uint8_t Cmd;
	uint8_t CmdOk;
	uint8_t HaveNewData;
	uint8_t ErrCount;
	uint8_t ErrMax;
	uint8_t Status;
	/*
	* Mode
	* 1:有RC4加密的接受数据的方法（包头包尾）
	* 2：没有RC4加密的接受数据的方法（包头包尾）
	* 3：有RC4加密的接受数据的方法（没有包头包尾）
	* 4：没有RC4加密的接受数据的方法（没有包头包尾）
	*/
	uint8_t Mode;
} CMD_BUF;     //命令结构体


#define	C_CommRxBufLen		256
#define	C_CommTxBufLen		128

/* 宏定义 --------------------------------------------------------------------*/
#define	C_CmdBufTotal			2
#define Packet_Header 		'*'
#define Packet_End 				'~'
#define Packet_error			0xE0

#define RXBUFSIZE           64 /* RX buffer size */
#define TXBUFSIZE           64 /* TX buffer size */

#define	C_CMD_RX_BUF_LEN		512

#define	CommCmdRxBuf	cmdBuf[0]
#define	CommCmdTxBuf	cmdBuf[1]

/*
* 选择接受数据的模式
*/
#define _RxMode_RC4_EndHeader 		 0x01
#define _RxMode_EndHeader          0x02
#define _RxMode_RC4_NoEndHeader    0x03
#define _RxMode_NoEndHeader				 0x04

/* 函数声明 ------------------------------------------------------------------*/
void ReceiveStr(void);
uint8_t StrCompare(const uint8_t *str1 , const uint8_t *str2 , const uint32_t length);
void StrCopy(uint8_t *destStr , const uint8_t *srcStr , const uint32_t length);
uint8_t CmdBufInit(CMD_BUF *cmdPtr , uint8_t *cmdStrBuf , const uint32_t bufLength
	                 ,const uint32_t errorsMax , const uint32_t overTime);
uint32_t GetCheckSum(volatile uint8_t *addrSrc , const uint32_t packetLength);
uint32_t AssembleCmd2Send_Hex(CMD_BUF* cmdPtr, const uint8_t cmdType, const uint8_t cmdCode, 
                     const uint8_t* paramBuf, const uint16_t paramLength);

uint32_t AssembleCmd2SendSimple_Hex
(CMD_BUF *cmdPtr,const uint8_t* paramBuf, const uint16_t paramLength);

uint8_t CmdSaveStr(CMD_BUF* cmdPtr, uint8_t data);
void CmdTimeCtrl(void);

void CmnCmdInit(void);
void CmdStrToData(CMD_BUF* cmdPtr);
void CmdResetOverTime(CMD_BUF* cmdPtr);
void CmdRxOvertimeCheck(CMD_BUF* cmdPtr);
void CmdCheckData(CMD_BUF* cmdPtr);
void CmdStrToData_Simple(CMD_BUF* cmdPtr);

void DataReceiveSyntaxHandle(const uint8_t modeSelected);
#endif
