#ifndef __THINK_GATE_H_
#define __THINK_GATE_H_
#include "stm32f0xx.h"
#include "flash_program.h"
#include "verfint.h"

#define KEY_ADDRESS 0x08007C00
#define COMMAND_LENGTH 41
#define LOCKINFO_LENGTH 27

#define GET_LOCK_INFO 0x01
#define OPEN_LOCK 0x02


typedef struct
{
	uint8_t keyInit[9];
	uint8_t keyCommun[9];
}keyGet;

typedef struct
{
	uint8_t Command;
	uint8_t header;
	uint8_t type;
	uint8_t PL_MSB;
	uint8_t PL_LSB;
	uint8_t Param;
	uint8_t Checksum;
	uint8_t End;
}commandInfo;

void SaveKey(uint32_t addrForKey,uint8_t *initializationKey,uint32_t initializationKeyLen,
	           uint8_t * communicationKey,uint32_t communicationKeyLen);
keyGet GetKey(const uint32_t keyAddressForKey,const uint32_t initializationKeyLen,const uint32_t communicationKeyLen);

void SendFacilityInfo(void);
uint8_t GetInfo(void);
void Arc4Decrypt(uint8_t *textBuf, uint32_t strLength,uint8_t *key);
void Arc4Crypt(uint8_t *textBuf,uint32_t hexLength);

uint8_t BleConnectedCheck(void);
void MsgHandle(void);


void Arc4Test(void);

#endif
