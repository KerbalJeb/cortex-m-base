#include <array>
#include <FreeRTOS.h>
#include <task.h>
#include "gpio.hpp"

[[noreturn]] void testTask (void *);
constexpr std::size_t TestStackSize = configMINIMAL_STACK_SIZE;
StaticTask_t          testTaskBuffer;
StackType_t           testTaskStack[TestStackSize];

constexpr gpio::Pin SS_RELAY_PIN = gpio::Pin::B0;

constexpr std::array gpio_config{
    gpio::ConfigStruct{SS_RELAY_PIN, gpio::Mode::output}
};

int main ()
{
  gpio::init(gpio_config.begin(), gpio_config.end());

  (void)xTaskCreateStatic (testTask, "tst", TestStackSize, nullptr, 1, testTaskStack, &testTaskBuffer);

  vTaskStartScheduler ();

  return 0;
}

[[noreturn]] void testTask (void *)
{
  while (true)
  {
    gpio::toggle(SS_RELAY_PIN);
    vTaskDelay (pdMS_TO_TICKS(1000));
  }
}