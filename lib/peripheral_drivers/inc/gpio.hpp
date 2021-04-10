/** @file gpio.hpp
*   @brief Created on 2021-03-24 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/

#include <algorithm>
#include <common.hpp>
#include <gpio_config.hpp>
#include <vector>

/**********************************************************************
* Constant Expressions
**********************************************************************/

/**********************************************************************
* Types
**********************************************************************/


/**********************************************************************
* Function Prototypes
**********************************************************************/

namespace gpio
{
template<typename T> concept ConfigIter = IterFor<T, ConfigStruct>;

void configure_pin (const gpio::ConfigStruct &config);

void init (ConfigIter auto begin, ConfigIter auto end)
{ std::for_each (begin, end, &configure_pin); }

void write (Pin gpio_pin, pin_state state);
void toggle (Pin gpio_pin);
pin_state read (Pin gpio_pin);
}