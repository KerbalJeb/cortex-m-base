/** @file gpio.cpp.c
*   @brief Created on 2021-03-24 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/


#include <gpio.hpp>
#include <stm32f0xx.h>
#include "volatile_op.hpp"

namespace
{

struct GpioPortInfo
{
  GPIO_TypeDef *port;
  uint32_t     ahb_clk_enable_bit;
};

const GpioPortInfo ports[]{
    {GPIOA, RCC_AHBENR_GPIOAEN},
    {GPIOB, RCC_AHBENR_GPIOBEN},
};
}



namespace
{
template<typename T>
inline void store_in_gpio_reg (T value, volatile uint32_t *reg, uint32_t mask, uint32_t offset)
{
  auto r = volatile_load (reg);
  r &= ~(mask << offset);
  r |= static_cast<const uint32_t>(value) << offset;
  volatile_store (reg, r);
}

inline auto get_port_info(gpio::Pin pin)
{
  auto pin_number = static_cast<const uint32_t>(pin);
  auto port_idx   = pin_number / pins_per_port;

  return ports[port_idx];
}

inline auto get_pin_idx(gpio::Pin pin)
{
  auto pin_number = static_cast<const uint32_t>(pin);
  auto pin_idx    = pin_number % pins_per_port;
  return pin_idx;
}

}
/**********************************************************************
* Function Definitions
**********************************************************************/

void gpio::write (gpio::Pin gpio_pin, gpio::pin_state state)
{
  auto pin_number  = static_cast<const uint32_t>(gpio_pin);
  auto pin_idx     = pin_number % pins_per_port;
  auto port_idx    = pin_number / pins_per_port;
  auto port_config = ports[port_idx];
  auto PORT        = port_config.port;

  if (state == high)
  {
    PORT->BSRR = 1 << pin_idx;
  }
  else
  {
    PORT->BRR = 1 << pin_idx;
  }

}
gpio::pin_state gpio::read (gpio::Pin gpio_pin)
{
  auto pin_number  = static_cast<const uint32_t>(gpio_pin);
  auto pin_idx     = pin_number % pins_per_port;
  auto port_idx    = pin_number / pins_per_port;
  auto port_config = ports[port_idx];
  auto PORT        = port_config.port;

  auto idr  = volatile_load (&PORT->IDR);
  auto mask = 1 << pin_idx;
  return static_cast<gpio::pin_state>((idr & mask) >> pin_idx);
}
void gpio::toggle (gpio::Pin gpio_pin)
{
  auto pin_number  = static_cast<const uint32_t>(gpio_pin);
  auto pin_idx     = pin_number % pins_per_port;
  auto port_idx    = pin_number / pins_per_port;
  auto port_config = ports[port_idx];
  auto PORT        = port_config.port;

  auto odr = volatile_load(&PORT->ODR);
  odr ^= 1 << pin_idx;
  volatile_store(&PORT->ODR, odr);
}
void gpio::configure_pin (const gpio::ConfigStruct &config)
{
  auto pin_idx    = get_pin_idx(config.pin);
  auto port_config = get_port_info(config.pin);

  auto PORT        = port_config.port;

  /* Enable Clock */
  auto ahbenr = volatile_load (&RCC->AHBENR);
  ahbenr |= port_config.ahb_clk_enable_bit;
  volatile_store (&RCC->AHBENR, ahbenr);

  /* Set Configuration */

  store_in_gpio_reg (config.mode, &PORT->MODER, 0b11, 2 * pin_idx);
  store_in_gpio_reg (config.pull_mode, &PORT->PUPDR, 0b11, 2 * pin_idx);

  /* Set to highest speed */
  store_in_gpio_reg (0x3, &PORT->OSPEEDR, 0b11, 2 * pin_idx);
  store_in_gpio_reg (config.initial_state, &PORT->ODR, 0b1, pin_idx);
  store_in_gpio_reg (config.output_mode, &PORT->OTYPER, 0b1, pin_idx);

  /* Set Alternate Function Mode */

  if (config.mode == Mode::af_mode)
  {
    uint32_t af_register_idx = pin_idx / 8;
    uint32_t af_offset       = pin_idx % 8;

    auto r = volatile_load (&PORT->AFR[af_register_idx]);

    r &= ~(0b1111 << af_offset * 4);
    r |= static_cast<const uint32_t>(config.alternate_function) << af_offset * 4;

    volatile_store (&PORT->AFR[af_register_idx], r);
  }
}
