add_library(periph STATIC
    src/adc.cpp
    src/gpio.cpp
    src/spi.cpp
    src/tim.cpp
    src/uart.cpp
)

target_include_directories(periph
    PUBLIC
        include
)

target_link_libraries(periph
    PUBLIC
        idf::freertos
    PRIVATE
        idf::esp8266
)
