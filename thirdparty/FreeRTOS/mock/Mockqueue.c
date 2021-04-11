/** @file Mockqueue.c
*   @brief Created on 2021-03-26 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "Mockqueue.h"


DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueGenericSendFromISR, QueueHandle_t, const void *, BaseType_t *, BaseType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueGiveFromISR, QueueHandle_t, BaseType_t *)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueReceiveFromISR, QueueHandle_t, void *, BaseType_t*)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueReceive, QueueHandle_t, void * , TickType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueIsQueueEmptyFromISR, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueIsQueueFullFromISR, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(UBaseType_t, uxQueueMessagesWaitingFromISR, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueCRSendFromISR, QueueHandle_t, const void *, BaseType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueCRReceiveFromISR, QueueHandle_t, void *, BaseType_t*)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueCRSend, QueueHandle_t, const void *, TickType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueCRReceive, QueueHandle_t, void *, TickType_t)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueCreateMutex, uint8_t)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueCreateMutexStatic, uint8_t, StaticQueue_t *)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueCreateCountingSemaphore, UBaseType_t, UBaseType_t)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueCreateCountingSemaphoreStatic, UBaseType_t, UBaseType_t, StaticQueue_t*)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueSemaphoreTake, QueueHandle_t, TickType_t)
DEFINE_FAKE_VALUE_FUNC(TaskHandle_t, xQueueGetMutexHolder, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(TaskHandle_t, xQueueGetMutexHolderFromISR, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueTakeMutexRecursive, QueueHandle_t, TickType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueGiveMutexRecursive, QueueHandle_t)
DEFINE_FAKE_VOID_FUNC(vQueueAddToRegistry, QueueHandle_t, const char *)
DEFINE_FAKE_VOID_FUNC(vQueueUnregisterQueue, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(const char *, pcQueueGetName, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueGenericCreate, UBaseType_t, UBaseType_t, uint8_t)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueGenericCreateStatic, UBaseType_t, UBaseType_t, uint8_t *, StaticQueue_t *, uint8_t)
DEFINE_FAKE_VALUE_FUNC(QueueHandle_t, xQueueCreateSet, UBaseType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueAddToSet, QueueSetMemberHandle_t, QueueSetHandle_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueRemoveFromSet, QueueSetMemberHandle_t, QueueSetHandle_t)
DEFINE_FAKE_VALUE_FUNC(QueueSetMemberHandle_t, xQueueSelectFromSet, QueueSetHandle_t, TickType_t)
DEFINE_FAKE_VALUE_FUNC(QueueSetMemberHandle_t, xQueueSelectFromSetFromISR, QueueSetHandle_t)
DEFINE_FAKE_VOID_FUNC(vQueueWaitForMessageRestricted, QueueSetHandle_t, TickType_t, BaseType_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueGenericReset, QueueHandle_t, BaseType_t)
DEFINE_FAKE_VOID_FUNC(vQueueSetQueueNumber, QueueSetHandle_t, UBaseType_t)
DEFINE_FAKE_VALUE_FUNC(UBaseType_t, uxQueueGetQueueNumber, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(uint8_t, ucQueueGetQueueType, QueueHandle_t)
DEFINE_FAKE_VALUE_FUNC(BaseType_t, xQueueGenericSend, QueueHandle_t, const void*, TickType_t, const BaseType_t)

