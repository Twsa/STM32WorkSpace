#ifndef __FLASH_PROGRAM_H_
#define __FLASH_PROGRAM_H_
#include "stm32f0xx.h"
void FlashWrite(uint32_t addr,uint8_t *data,uint32_t len);
void FlashRead(uint32_t addr,const uint32_t len);

void  FlashOperationPreparation(void);
void  FlashErase(uint32_t page_addr);
void CheckFlashErase(uint32_t first_page_addr);
void FlashWord16Prog(uint32_t flash_addr, uint16_t data);
#endif
