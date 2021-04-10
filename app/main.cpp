#include <array>
#include <FreeRTOS.h>
#include <task.h>
#include "usb_serial.hpp"
#include "command_line.hpp"

int main ()
{
  RCC->CR2 |= RCC_CR2_HSI48ON;
  while (!(RCC->CR2 & RCC_CR2_HSI48RDY)){}
  RCC->CFGR = RCC_CFGR_SW_HSI48;
  RCC->CR &= ~RCC_CR_PLLON;
  FLASH->ACR = FLASH_ACR_PRFTBE | 0x1;

  RCC->APB1ENR |= RCC_APB1ENR_USBEN;

  command_line::init();
  vTaskStartScheduler ();

  return 0;
}
