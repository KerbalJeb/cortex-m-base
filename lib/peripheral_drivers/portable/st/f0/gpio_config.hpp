/** @file gpio_port.hpp
*   @brief Created on 2021-03-24 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/
#include <cstdint>
/**********************************************************************
* Constant Expressions
**********************************************************************/
constexpr std::size_t pins_per_port = 16;

/**********************************************************************
* Types
**********************************************************************/


namespace gpio
{
/**
 * @enum gpio::pin_state
 * @brief Defines the possible states for a digital output pin.
 */
enum pin_state
{
  low,
  high,
};

/**
 * @enum gpio::pin
 * @brief Defines all of the pins on the MCU
 */
enum class Pin : uint32_t
{
  A0,
  A1,
  A2,
  A3,
  A4,
  A5,
  A6,
  A7,
  A8,
  A9,
  A10,
  A11,
  A12,
  A13,
  A14,
  A15,
  B0,
  B1,
  B2,
  B3,
  B4,
  B5,
  B6,
  B7,
  B8,
  END,
};

/**
 * @enum gpio::mode
 * @brief Defines all possible GPIO multiplexing values/modes.
 */
enum class Mode : uint32_t
{
  input   = 0b00, /**< Digital Input */
  output  = 0b01, /**< Digital Output */
  af_mode = 0b10, /**< Alternate Function Mode */
  analog  = 0b11, /**< For ADC/DAC */
};

/**
 * @enum gpio::pull_mode
 * @brief Defines all possible GPIO pull up/down states
 */
enum class PullMode : uint32_t
{
  none = 0b00, /**< Pull up/down resistor disabled */
  up   = 0b01, /**< Pull up enabled */
  down = 0b10, /**< Pull down enabled */
};

/**
 * @enum gpio::alternate_function
 * @brief Defines all alternate function modes
 */
enum class AlternateFunction
{
  mode0,
  mode1,
  mode2,
  mode3,
  mode4,
  mode5,
  mode6,
  mode7,
};

/**
 * @enum gpio::output_mode
 * @brief Defines the pins output mode as push pull or open drain
 */
enum class OutputMode
{
  push_pull_output  = 0, /**< VCC on high and GND on low */
  open_drain_output = 1, /**< Floating on high and GND on low*/
};

/**
 * @struct gpio::config_struct
 * @brief Defines the configuration for a GPIO pin
 */
struct ConfigStruct
{
  Pin               pin;
  Mode              mode;
  PullMode          pull_mode;
  AlternateFunction alternate_function;
  pin_state         initial_state;
  OutputMode        output_mode;
};
}
