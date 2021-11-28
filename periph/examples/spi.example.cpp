#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "periph/gpio.hpp"
#include "periph/spi.hpp"

struct main_task_ctx_t
{
    periph::spi *spi;
    periph::gpio *cs;
};

static void main_task(void *pvParameters)
{
    main_task_ctx_t *ctx = (main_task_ctx_t *)pvParameters;
    periph::spi &_spi = *ctx->spi;
    periph::gpio &_cs = *ctx->cs;
    
    while(1)
    {
        uint8_t buff[200];
        
        for(size_t i = 0; i < sizeof(buff); i++)
            buff[i] = i;
        
        _spi.write(buff, sizeof(buff), &_cs);
        
        vTaskDelay(1000);
    }
}

// uart baud rate is 74880
extern "C" void app_main(void)
{
    static periph::gpio spi1_miso(0, 12, periph::gpio::mode::AF3);
    static periph::gpio spi1_mosi(0, 13, periph::gpio::mode::AF3);
    static periph::gpio spi1_clk(0, 14, periph::gpio::mode::AF3);
    static periph::gpio spi1_cs(0, 15, periph::gpio::mode::DO);
    
    static periph::spi spi1(periph::spi::SPI_1, 1000000, periph::spi::CPOL_0,
        periph::spi::CPHA_0, periph::spi::BIT_ORDER_MSB, spi1_mosi, spi1_miso,
        spi1_clk);
    
    static main_task_ctx_t ctx = {.spi = &spi1, .cs = &spi1_cs};
    
    xTaskCreate(main_task, "main", configMINIMAL_STACK_SIZE, &ctx,
        tskIDLE_PRIORITY + 1, nullptr);
}
