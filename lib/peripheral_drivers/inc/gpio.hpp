/** @file gpio.hpp
*   @brief Created on 2021-03-24 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/
#include <concepts>
#include <iterator>
#include <algorithm>

#include <gpio_config.hpp>
#include <vector>

/**********************************************************************
* Constant Expressions
**********************************************************************/

/**********************************************************************
* Types
**********************************************************************/

template<typename T, typename Base>
concept IterFor = requires(T it){ std::is_same<decltype (*it), Base>::value; } && std::forward_iterator<T>;

template<typename T> concept ConfigIter = IterFor < T, gpio::ConfigStruct>;

/**********************************************************************
* Function Prototypes
**********************************************************************/

namespace gpio
{
void configure_pin(const gpio::ConfigStruct& config);

void init (ConfigIter auto begin, ConfigIter auto end)
{
  std::for_each(begin, end, &configure_pin);
}

void write (Pin gpio_pin, pin_state state);
void toggle (Pin gpio_pin);
pin_state read (Pin gpio_pin);
}