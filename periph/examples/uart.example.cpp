#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "periph/gpio.hpp"
#include "periph/uart.hpp"

static void main_task(void *pvParameters)
{
    periph::uart &_uart = *((periph::uart *)pvParameters);
    
    while(1)
    {
        _uart.write("uart test\n", sizeof("uart test\n") - 1);
        
        /* Example of reading:
        uint8_t buff[100];
        size_t size;
        memset(buff, 0, sizeof(buff));
        size = sizeof(buff);
        _uart.read(buff, &size, portMAX_DELAY); */
        
        /* Example of full duplex transferring:
        uint8_t buff[100];
        size_t size;
        memset(buff, 0, sizeof(buff));
        size = sizeof(buff);
        _uart.exch("mytest", sizeof("mytest") - 1, buff, &size, portMAX_DELAY); */
        
        vTaskDelay(500);
    }
}

// uart baud rate is 74880
extern "C" void app_main(void)
{
    /* To be able to use UART0, don't forget to set CONFIG_CONSOLE_UART_NUM to 1
    in sdkconfig.h. To be able to use printf() from SDK - initialize uart1_tx
    (GPIO2) like in example below */

    static periph::gpio uart0_tx(0, 1, periph::gpio::mode::AF1);
    static periph::gpio uart0_rx(0, 3, periph::gpio::mode::AF1);
    static periph::uart uart0(periph::uart::UART_0, 115200, periph::uart::STOPBIT_1,
        periph::uart::PARITY_NONE, &uart0_tx, &uart0_rx);
    
    /* Initializing UART1:
    static periph::gpio uart1_tx(0, 2, periph::gpio::mode::AF2);
    static periph::uart uart1(periph::uart::UART_1, 115200, periph::uart::STOPBIT_1,
        periph::uart::PARITY_NONE, &uart1_tx, nullptr); */
    
    xTaskCreate(main_task, "main", configMINIMAL_STACK_SIZE, &uart0,
        tskIDLE_PRIORITY + 1, nullptr);
}
