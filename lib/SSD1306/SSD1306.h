/** @file SSD1306.h
*   @brief Created on 2021-03-15 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/
#include <cstdint>
#include "i2c.h"
#include "fonts.h"

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

void ssd1306_init(uint8_t slaveAddress, I2C_Channel i2CChannel);
void ssd1306_clear_display();
void ssd1306_write_string(const char* string, uint8_t line, uint8_t charPos);
void ssd1306_write_char(const uint8_t *charTable, uint8_t line, uint8_t charPos);

#ifdef __cplusplus
} // extern "C"
#endif