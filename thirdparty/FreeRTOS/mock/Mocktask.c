/** @file Mocktas.c
*   @brief Created on 2021-03-26 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "Mocktask.h"

/**********************************************************************
* Function Definitions
**********************************************************************/


DEFINE_FAKE_VALUE_FUNC(uint32_t, ulTaskGenericNotifyTake, UBaseType_t, BaseType_t, TickType_t) ;
DEFINE_FAKE_VALUE_FUNC(TaskHandle_t, xTaskGetCurrentTaskHandle) ;
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xTaskGenericNotify, TaskHandle_t, UBaseType_t, uint32_t, eNotifyAction, uint32_t*) ;
