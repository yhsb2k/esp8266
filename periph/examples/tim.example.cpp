#include "FreeRTOS.h"
#include "task.h"
#include "periph/gpio.hpp"
#include "periph/tim.hpp"

static void main_task(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(500);
    }
}

static void tim_cb(periph::tim *tim, void *ctx)
{
    periph::gpio *blue_led = (periph::gpio *)ctx;
    
    blue_led->toggle();
}

// uart baud rate is 74880
extern "C" void app_main(void)
{
    static periph::gpio blue_led(0, 2, periph::gpio::mode::DO, 1);
    
    static periph::tim tim1(periph::tim::TIM_1);
    tim1.cb(tim_cb, &blue_led);
    tim1.us(200000);
    tim1.start(true);
    
    xTaskCreate(main_task, "main", configMINIMAL_STACK_SIZE, nullptr,
        tskIDLE_PRIORITY + 1, nullptr);
}
