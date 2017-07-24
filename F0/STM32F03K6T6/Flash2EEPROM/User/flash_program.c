#include "flash_program.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size */
#define FLASH_USER_START_ADDR   ((uint32_t)0x08007C00)   /* Start @ of user Flash area */
#define DATA_TO_PROG            ((uint32_t)0xAABBCCDD)   /* 32-bits value to be programmed */

/* Error codes used to make the orange led blinking */
#define ERROR_ERASE 0x01
#define ERROR_PROG  0x02
#define ERROR_PROG_FLAG 0x04
#define ERROR_WRITE_PROTECTION 0x08
#define ERROR_UNKNOWN 0x10

/* Delay value : short one is used for the error coding, long one in case of no error
   or between two bursts */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint16_t error = 0;             //initialized at 0 and modified by the functions 
uint32_t test_to_be_performed_twice = 1; //this variable is set to 2 if the first address of the page to erase is yet erased

/* Private function prototypes -----------------------------------------------*/
//void  ConfigureGPIO(void);

extern void    FLASH_PageErase(uint32_t PageAddress);
/*************************************************************************************
*  Function Name                    :    FlashWrite
*  Create Date                      :    2017/07/24
*  Author/Corporation               :    Twsa Liu
*  Description                      :    对FLASH进行编程
                                        
*  Param                            :    addr;data
*  Return Code                      :    None
																			
*  Global Variable                  :    
*  File Static Variable             :    None
*  Function Static Variable         :    None
																			 
*--------------------------------Revision History--------------------------------------
*  No         Version         Date        RevisedBy        Item         Description  
*  1          V1.0            2017/07/24  Twsa Liu         None           None
**************************************************************************************/
void FlashWrite(void)
{
	uint32_t testBuf=0;
	
  FlashOperationPreparation();
  /* Check if the first address of the page is yet erased,this is only for this example */
  if (*(uint32_t *)(FLASH_USER_START_ADDR) == (uint32_t)0xFFFFFFFF) 
  {
    test_to_be_performed_twice = 2;
  }
  
  while (test_to_be_performed_twice-- > 0)
  {
    FlashErase(FLASH_USER_START_ADDR);
    CheckFlashErase(FLASH_USER_START_ADDR);
    FlashWord16Prog(FLASH_USER_START_ADDR, (uint16_t)DATA_TO_PROG);
    FlashWord16Prog(FLASH_USER_START_ADDR + 2, (uint16_t)(DATA_TO_PROG >> 16));
    
    /* Check the programming of the address */
    if  ((*(uint32_t *)(FLASH_USER_START_ADDR)) != DATA_TO_PROG)
    {
      error |= ERROR_PROG;
    }
  }
	testBuf=(uint32_t) * (uint32_t *)FLASH_USER_START_ADDR;
	printf("testBuf:%x\r\n",testBuf);
}

/**
  * @brief  This function prepares the flash to be erased or programmed.
  *         It first checks no flash operation is on going,
  *         then unlocks the flash if it is locked.
  * @param  None
  * @retval None
  */
__INLINE void FlashOperationPreparation(void)
{  
  /* (1) Wait till no operation is on going */
  /* (2) Check that the Flash is unlocked */
  /* (3) Perform unlock sequence */
  while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (1) */  
  {
    /* For robust implementation, add here time-out management */
  }  
  if ((FLASH->CR & FLASH_CR_LOCK) != 0) /* (2) */
  {    
    FLASH->KEYR = (uint32_t)0x45670123; /* (3) */
    FLASH->KEYR = (uint32_t)0xCDEF89AB;
  }
}
/**
  * @brief  This function erases a page of flash.
  *         The Page Erase bit (PER) is set at the beginning and reset at the end
  *         of the function, in case of successive erase, these two operations
  *         could be performed outside the function.
  * @param  page_addr is an address inside the page to erase
  * @retval None
  */
__INLINE void FlashErase(uint32_t page_addr)
{   
  /* (1) Set the PER bit in the FLASH_CR register to enable page erasing */
  /* (2) Program the FLASH_AR register to select a page to erase */
  /* (3) Set the STRT bit in the FLASH_CR register to start the erasing */
  /* (4) Wait until the BSY bit is reset in the FLASH_SR register */
  /* (5) Check the EOP flag in the FLASH_SR register */
  /* (6) Clear EOP flag by software by writing EOP at 1 */
  /* (7) Reset the PER Bit to disable the page erase */
  FLASH->CR |= FLASH_CR_PER; /* (1) */    
  FLASH->AR =  page_addr; /* (2) */    
  FLASH->CR |= FLASH_CR_STRT; /* (3) */    
  while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (4) */ 
  {
    /* For robust implementation, add here time-out management */
  }  
  if ((FLASH->SR & FLASH_SR_EOP) != 0)  /* (5) */
  {  
    FLASH->SR |= FLASH_SR_EOP; /* (6)*/
  }    
  /* Manage the error cases */
  else if ((FLASH->SR & FLASH_SR_WRPERR) != 0) /* Check Write protection error */
  {
    error |= ERROR_WRITE_PROTECTION; /* Report the error to the main progran */
    FLASH->SR |= FLASH_SR_WRPERR; /* Clear the flag by software by writing it at 1*/
  }
  else
  {
    error |= ERROR_UNKNOWN; /* Report the error to the main progran */
  }
  FLASH->CR &= ~FLASH_CR_PER; /* (7) */
}


/**
  * @brief  This function checks that the whole page has been correctly erased
  *         A word is erased while all its bits are set.
  * @param  first_page_addr is the first address of the page to erase
  * @retval None
  */
__INLINE void CheckFlashErase(uint32_t first_page_addr)
{
uint32_t i;  

  for (i=FLASH_PAGE_SIZE; i > 0;i-=4) /* Check the erasing of the page by reading all the page value */
  {
    if (*(uint32_t *)(first_page_addr + i -4) != (uint32_t)0xFFFFFFFF) /* compare with erased value, all bits at1 */
    {
      error |= ERROR_ERASE; /* report the error to the main progran */
    }
  }
}

/**
  * @brief  This function programs a 16-bit word.
  *         The Programming bit (PG) is set at the beginning and reset at the end
  *         of the function, in case of successive programming, these two operations
  *         could be performed outside the function.
  *         This function waits the end of programming, clears the appropriate bit in 
  *         the Status register and eventually reports an error. 
  * @param  flash_addr is the address to be programmed
  *         data is the 16-bit word to program
  * @retval None
  */
__INLINE void FlashWord16Prog(uint32_t flash_addr, uint16_t data)
{    
  /* (1) Set the PG bit in the FLASH_CR register to enable programming */
  /* (2) Perform the data write (half-word) at the desired address */
  /* (3) Wait until the BSY bit is reset in the FLASH_SR register */
  /* (4) Check the EOP flag in the FLASH_SR register */
  /* (5) clear it by software by writing it at 1 */
  /* (6) Reset the PG Bit to disable programming */
  FLASH->CR |= FLASH_CR_PG; /* (1) */
  *(__IO uint16_t*)(flash_addr) = data; /* (2) */
  while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (3) */
  {
    /* For robust implementation, add here time-out management */
  }  
  if ((FLASH->SR & FLASH_SR_EOP) != 0)  /* (4) */
  {
    FLASH->SR |= FLASH_SR_EOP; /* (5) */
  }
  /* Manage the error cases */
  else if ((FLASH->SR & FLASH_SR_PGERR) != 0) /* Check Programming error */
  {      
    error = ERROR_PROG_FLAG;
    FLASH->SR |= FLASH_SR_PGERR; /* Clear it by software by writing EOP at 1*/
  }
  else if ((FLASH->SR & FLASH_SR_WRPERR) != 0) /* Check write protection */
  {      
    error = ERROR_WRITE_PROTECTION; 
    FLASH->SR |= FLASH_SR_WRPERR; /* Clear it by software by writing it at 1*/
  }
  else
  {
    error = ERROR_UNKNOWN; 
  }
  FLASH->CR &= ~FLASH_CR_PG; /* (6) */
}
