/** @file f0_cmsis.hpp.h
*   @brief Created on 2021-03-24 by Ben
*/



/**********************************************************************
* Includes
**********************************************************************/
#include_next <stm32f0xx.h>

#ifndef STM32FXX_MOCK
#define STM32FXX_MOCK
/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

typedef struct
{
  /* AHB2 */
  GPIO_TypeDef gpioa;
  GPIO_TypeDef gpiob;
  GPIO_TypeDef gpioc;
  GPIO_TypeDef gpioe;
  GPIO_TypeDef gpiof;

  /* AHB1  */
  TSC_TypeDef   tsc;
  CRC_TypeDef   crc;
  FLASH_TypeDef flash;
  RCC_TypeDef   rcc;
  DMA_TypeDef   dma2;
  DMA_TypeDef   dma;

  /* APH */
  DBGMCU_TypeDef dbgmcu;
  TIM_TypeDef    tim17;
  TIM_TypeDef    tim16;
  TIM_TypeDef    tim15;
  USART_TypeDef  usart1;
  SPI_TypeDef    spi1;
  TIM_TypeDef    tim1;
  ADC_TypeDef    adc;
  USART_TypeDef  usart8;
  USART_TypeDef  usart7;
  USART_TypeDef  usart6;
  EXTI_TypeDef   exti;
  SYSCFG_TypeDef syscfg;
  CEC_TypeDef    cec;
  PWR_TypeDef    pwr;
  CRS_TypeDef    crs;
  CAN_TypeDef    can;
  uint16_t       USB_SRAM[512];
  USB_TypeDef    usb;
  I2C_TypeDef    i2c2;
  I2C_TypeDef    i2c1;
  USART_TypeDef  usart5;
  USART_TypeDef  usart4;
  USART_TypeDef  usart3;
  USART_TypeDef  usart2;
  SPI_TypeDef    spi2;
  IWDG_TypeDef   iwdg;
  WWDG_TypeDef   wwdg;
  RTC_TypeDef    rtc;
  TIM_TypeDef    tim14;
  TIM_TypeDef    tim7;
  TIM_TypeDef    tim6;
  TIM_TypeDef    tim3;
  TIM_TypeDef    tim2;
}PeripheralRegisters;

extern PeripheralRegisters MockRegisters;

/**********************************************************************
* AHB2
**********************************************************************/
#undef  GPIOA
#define GPIOA (&MockRegisters.gpioa)

#undef  GPIOB
#define GPIOB (&MockRegisters.gpiob)

#undef  GPIOC
#define GPIOC (&MockRegisters.gpioc)

#undef  GPIOD
#define GPIOD (&MockRegisters.gpiod)

#undef  GPIOE
#define GPIOE (&MockRegisters.gpioe)

#undef  GPIOF
#define GPIOF (&MockRegisters.gpiof)


/**********************************************************************
* AHB1
**********************************************************************/

#undef  RCC
#define RCC (&MockRegisters.rcc)

#undef  SPI1
#define SPI1 (&MockRegisters.spi1)

#undef  SPI2
#define SPI2 (&MockRegisters.spi2)

#endif