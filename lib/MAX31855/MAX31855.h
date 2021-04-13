/** @file MAX31855.h
*   @brief Created on 2021-03-11 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
#include "gpio.h"
#include "spi.h"
#include <stdint.h>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

struct Max31855QuickReading{
    int16_t temperature_times_4;
    bool fault;
};

struct Max31855FullReading{
    int16_t temperature_times_4;
    int16_t internal_temperature_times_16;
    bool vcc_short;
    bool gnd_short;
    bool open_circuit;
};

/**********************************************************************
* Function Prototypes
**********************************************************************/

void max31855_init(enum SpiChannel spiChannel, enum GpioChannel csPin);
void max31855_quick_read(struct Max31855QuickReading* reading);
void max31855_full_read(struct Max31855FullReading* reading);

#ifdef __cplusplus
} // extern "C"
#endif