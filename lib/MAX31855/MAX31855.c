/** @file MAX31855.c
*   @brief Created on 2021-03-11 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "MAX31855.h"
#include "FreeRTOS.h"
#include "task.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
static enum SpiChannel enumSpiChannel;
static enum GpioChannel chipSelectPin;
static uint8_t dataBuffer[4];

/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/

void max31855_init(enum SpiChannel spiChannel, enum GpioChannel csPin)
{
    enumSpiChannel = spiChannel;
    chipSelectPin = csPin;
    gpio_write(csPin, GPIO_HIGH);
}

void max31855_quick_read(struct Max31855QuickReading *reading)
{
    gpio_write(chipSelectPin, GPIO_LOW);
    spi_read(enumSpiChannel, dataBuffer, 2);
    gpio_write(chipSelectPin, GPIO_HIGH);
    int16_t tempSign = 1 - ((dataBuffer[0] & 0x80) >> 6);

    taskENTER_CRITICAL();
    reading->fault = dataBuffer[1] & 0x1;
    reading->temperature_times_4 = tempSign * ((dataBuffer[0] & 0x7f) << 6 | (dataBuffer[1] & 0xFc) >> 2);
    taskEXIT_CRITICAL();
}

void max31855_full_read(struct Max31855FullReading *reading)
{
    gpio_write(chipSelectPin, GPIO_LOW);
    spi_read(enumSpiChannel, dataBuffer, 4);
    gpio_write(chipSelectPin, GPIO_HIGH);

    int16_t tempSign = 1 - ((dataBuffer[0] & 0x80) >> 6);
    reading->temperature_times_4 = tempSign * ((dataBuffer[0] & 0x7f) << 6 | (dataBuffer[1] & 0xFc) >> 2);

    reading->open_circuit = (dataBuffer[3] & 0x1) >> 0;
    reading->gnd_short    = (dataBuffer[3] & 0x2) >> 1;
    reading->vcc_short    = (dataBuffer[3] & 0x4) >> 2;
    tempSign = 1 - ((dataBuffer[2] & 0x80) >> 6);
    reading->internal_temperature_times_16 = tempSign * (dataBuffer[2] & 0x7f) << 4 | (dataBuffer[3] & 0xf0) >> 4;
}
