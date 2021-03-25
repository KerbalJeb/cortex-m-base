/** @file gpio_test.cpp.c
*   @brief Created on 2021-03-24 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>
#include <vector>
#include "mocks/stm32f0xx.h"
#include "gpio.hpp"

/**********************************************************************
* Tests
**********************************************************************/

using namespace gpio;
using GpioRegistersTestConfig = std::tuple<std::string,
                                           uint32_t,
                                           uint32_t,
                                           uint32_t,
                                           gpio::ConfigStruct,
                                           volatile uint32_t *>;

class GpioInitTests : public testing::TestWithParam<GpioRegistersTestConfig>
{
};

TEST_P(GpioInitTests, bit_set_test)
{
  /* Param 0 is the name */
  auto params        = GetParam ();
  auto pos           = std::get<1> (params);
  auto value         = std::get<3> (params);
  auto config_struct = std::get<4> (params);
  auto reg           = std::get<5> (params);

  const gpio::ConfigStruct config[]{config_struct, {gpio::Pin::END},};

  *reg = 0;
  gpio::configure (config);
  ASSERT_EQ(*reg, value << pos);
}

TEST_P(GpioInitTests, bit_clear_test)
{
  /* Param 0 is the name */
  auto params        = GetParam ();
  auto pos           = std::get<1> (params);
  auto mask          = std::get<2> (params);
  auto value         = std::get<3> (params);
  auto config_struct = std::get<4> (params);
  auto reg           = std::get<5> (params);

  const gpio::ConfigStruct config[]{config_struct, {gpio::Pin::END},};

  *reg = 0xFFFFFFFF;
  gpio::configure (config);
  ASSERT_EQ(*reg, (0xFFFFFFFF & ~mask) | (value << pos));
}

TEST(GpioInitTests, multiple_pins_init)
{
  const gpio::ConfigStruct config[]{
      {Pin::A0,  Mode::input,},
      {Pin::A15, Mode::output,},
      {Pin::B0,  Mode::input,},
      {Pin::B7,  Mode::af_mode,},
      {Pin::END},
  };

  MockRegisters = PeripheralRegisters{};
  gpio::configure (config);

  ASSERT_THAT((std::vector{MockRegisters.gpioa.MODER, MockRegisters.gpiob.MODER}),
              testing::ElementsAre (
                  static_cast<uint32_t>(Mode::input) << GPIO_MODER_MODER0_Pos |
                  static_cast<uint32_t>(Mode::output) << GPIO_MODER_MODER15_Pos,
                  static_cast<uint32_t>(Mode::input) << GPIO_MODER_MODER0_Pos |
                  static_cast<uint32_t>(Mode::af_mode) << GPIO_MODER_MODER7_Pos
              ));

}

class GpioPinTests : public testing::TestWithParam<uint32_t>
{
 protected:
  void SetUp() override{
    MockRegisters = PeripheralRegisters{};
  }
};

TEST_P(GpioPinTests, pin_set_porta)
{
  auto pin = static_cast<const gpio::Pin>(GetParam());
  gpio::write(pin, gpio::high);
  ASSERT_EQ(MockRegisters.gpioa.BSRR, 1 << GetParam());
}

TEST_P(GpioPinTests, pin_clear_porta)
{
  auto pin = static_cast<const gpio::Pin>(GetParam());
  gpio::write(pin, gpio::low);
  ASSERT_EQ(MockRegisters.gpioa.BRR, 1 << GetParam());
}

TEST_P(GpioPinTests, pin_read_low_porta)
{
  auto pin = static_cast<const gpio::Pin>(GetParam());
  MockRegisters.gpioa.IDR = 0;
  ASSERT_EQ(gpio::read(pin), low);
}

TEST_P(GpioPinTests, pin_read_high_porta)
{
  auto pin = static_cast<const gpio::Pin>(GetParam());
  MockRegisters.gpioa.IDR = 1 << GetParam();
  ASSERT_EQ(gpio::read(pin), high);
}

TEST_P(GpioPinTests, pin_toggle_high_porta)
{
  auto pin = static_cast<const gpio::Pin>(GetParam());
  MockRegisters.gpioa.ODR = 0;
  gpio::toggle(pin);
  ASSERT_EQ(MockRegisters.gpioa.ODR, 1 << GetParam());
}

TEST_P(GpioPinTests, pin_toggle_low_porta)
{
  auto pin = static_cast<const gpio::Pin>(GetParam());
  MockRegisters.gpioa.ODR = 1 << GetParam();
  gpio::toggle(pin);
  ASSERT_EQ(MockRegisters.gpioa.ODR, 0);
}

TEST_P(GpioPinTests, pin_toggle_low_portb)
{
  auto pin = static_cast<const gpio::Pin>(GetParam() + 16);
  MockRegisters.gpiob.ODR = 1 << GetParam();
  gpio::toggle(pin);
  ASSERT_EQ(MockRegisters.gpiob.ODR, 0);
}

TEST_P(GpioPinTests, pin_read_high_portb)
{
  auto pin = static_cast<const gpio::Pin>(GetParam() + 16);
  MockRegisters.gpiob.IDR = 1 << GetParam();
  ASSERT_EQ(gpio::read(pin), high);
}

TEST_P(GpioPinTests, pin_set_portb)
{
  auto pin = static_cast<const gpio::Pin>(GetParam() + 16);
  gpio::write(pin, gpio::high);
  ASSERT_EQ(MockRegisters.gpiob.BSRR, 1 << GetParam());
}


INSTANTIATE_TEST_SUITE_P(PinTests, GpioPinTests, testing::Values(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15));

INSTANTIATE_TEST_SUITE_P(SingleRegTests, GpioInitTests,
                         testing::Values (
                             std::tuple{
                                 "ClockEnablePortA",
                                 RCC_AHBENR_GPIOAEN_Pos,
                                 RCC_AHBENR_GPIOAEN_Msk,
                                 0x1,
                                 gpio::ConfigStruct{.pin=gpio::Pin::A10},
                                 &MockRegisters.rcc.AHBENR
                             },
                             std::tuple{
                                 "ClockEnablePortVB",
                                 RCC_AHBENR_GPIOBEN_Pos,
                                 RCC_AHBENR_GPIOBEN_Msk,
                                 0x1,
                                 gpio::ConfigStruct{.pin=gpio::Pin::B8},
                                 &MockRegisters.rcc.AHBENR
                             },
                             std::tuple{
                                 "ModerSetOutput",
                                 GPIO_MODER_MODER10_Pos,
                                 GPIO_MODER_MODER10_Msk,
                                 static_cast<uint32_t>(gpio::Mode::output),
                                 gpio::ConfigStruct{.pin=gpio::Pin::A10, .mode=gpio::Mode::output},
                                 &MockRegisters.gpioa.MODER
                             },
                             std::tuple{
                                 "PullUpDownSetDown",
                                 GPIO_PUPDR_PUPDR10_Pos,
                                 GPIO_PUPDR_PUPDR10_Msk,
                                 static_cast<uint32_t>(gpio::PullMode::down),
                                 gpio::ConfigStruct{.pin=gpio::Pin::A10, .pull_mode=gpio::PullMode::down},
                                 &MockRegisters.gpioa.PUPDR
                             },
                             std::tuple{
                                 "OutputStateSetHigh",
                                 10,
                                 1 << 10,
                                 static_cast<uint32_t>(gpio::high),
                                 gpio::ConfigStruct{.pin=gpio::Pin::A10, .initial_state=gpio::high},
                                 &MockRegisters.gpioa.ODR
                             },
                             std::tuple{
                                 "OutputSpeedDefault",
                                 GPIO_OSPEEDR_OSPEEDR10_Pos,
                                 GPIO_OSPEEDR_OSPEEDR10_Msk,
                                 0x3,
                                 gpio::ConfigStruct{.pin=gpio::Pin::A10},
                                 &MockRegisters.gpioa.OSPEEDR
                             },
                             std::tuple{
                                 "OutputType",
                                 10,
                                 GPIO_OTYPER_OT_10,
                                 static_cast<uint32_t>(gpio::OutputMode::open_drain_output),
                                 gpio::ConfigStruct{.pin=gpio::Pin::A10, .output_mode=gpio::OutputMode::open_drain_output},
                                 &MockRegisters.gpioa.OTYPER
                             },
                             std::tuple{
                                 "AlternateFunctionSetAF5",
                                 GPIO_AFRH_AFRH2_Pos,
                                 GPIO_AFRH_AFRH2_Msk,
                                 static_cast<uint32_t>(gpio::AlternateFunction::mode5),
                                 gpio::ConfigStruct{
                                     .pin=gpio::Pin::A10,
                                     .mode=gpio::Mode::af_mode,
                                     .alternate_function=gpio::AlternateFunction::mode5
                                 },
                                 &MockRegisters.gpioa.AFR[1]
                             },
                             std::tuple{
                                 "AlternateFunctionSetPortB",
                                 GPIO_AFRH_AFRH0_Pos,
                                 GPIO_AFRH_AFRH0_Msk,
                                 static_cast<uint32_t>(gpio::AlternateFunction::mode5),
                                 gpio::ConfigStruct{
                                     .pin=gpio::Pin::B8,
                                     .mode=gpio::Mode::af_mode,
                                     .alternate_function=gpio::AlternateFunction::mode5
                                 },
                                 &MockRegisters.gpiob.AFR[1]
                             }
                         ),
                         [] (const testing::TestParamInfo<GpioInitTests::ParamType> &info)
                         { return std::get<0> (info.param); });