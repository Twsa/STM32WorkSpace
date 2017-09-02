#ifndef __POWER_CONTROL_H_
#define __POWER_CONTROL_H_
/*
* Private Includes
*/
#include "sys.h"

/*
* Private Macro Definition  
*/
#define Enter_StopMode  0x01
#define Exit_StopMode   0x02

/*
*/
void StopMode_Control(const uint8_t modeSelected);
#endif
