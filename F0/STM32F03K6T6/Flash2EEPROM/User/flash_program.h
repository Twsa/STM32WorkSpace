#ifndef __FLASH_PROGRAM_H_
#define __FLASH_PROGRAM_H_
#include "stm32f0xx.h"
void FlashWrite(void);
void  FlashOperationPreparation(void);
void  FlashErase(uint32_t page_addr);
void CheckFlashErase(uint32_t first_page_addr);
void FlashWord16Prog(uint32_t flash_addr, uint16_t data);
#endif
