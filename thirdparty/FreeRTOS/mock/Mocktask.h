/** @file Mocktask.h
*   @brief Created on 2021-03-27 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "fff.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FAKE_VALUE_FUNC(uint32_t, ulTaskGenericNotifyTake, UBaseType_t, BaseType_t, TickType_t) ;
DECLARE_FAKE_VALUE_FUNC(TaskHandle_t, xTaskGetCurrentTaskHandle) ;
DECLARE_FAKE_VALUE_FUNC(BaseType_t, xTaskGenericNotify, TaskHandle_t, UBaseType_t, uint32_t, eNotifyAction, uint32_t*) ;

#ifdef __cplusplus
}
#endif