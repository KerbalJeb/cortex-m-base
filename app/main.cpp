#include <cstdint>
#include <FreeRTOS.h>
#include <task.h>

[[noreturn]] void testTask(void *);
constexpr std::size_t TestStackSize = configMINIMAL_STACK_SIZE;
StaticTask_t testTaskBuffer;
StackType_t  testTaskStack[TestStackSize];

int main()
{
    xTaskCreateStatic(testTask, "tst", TestStackSize, nullptr, 1, testTaskStack, &testTaskBuffer);

    vTaskStartScheduler();

    return 0;
}

[[noreturn]] void testTask(void *)
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}