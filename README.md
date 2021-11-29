# esp8266 submodule of [mcu-framework](https://github.com/yhsb2k/mcu-framework)

[![build](https://github.com/yhsb2k/esp8266/workflows/build/badge.svg)](https://github.com/yhsb2k/esp8266/actions?workflow=build)
[![license](https://img.shields.io/github/license/yhsb2k/esp8266?color=blue)](https://github.com/yhsb2k/esp8266/blob/master/LICENSE)

## How to build
```
git clone --recursive https://github.com/yhsb2k/esp8266.git
cd esp8266
make
```
**Other targets:**
```
make flash - Upload firmware to the target
make erase - Erase all memory on the target
make reset - Reset the target
```

## Requirements
* [GNU Xtensa Embedded Toolchain](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html)
* [CMake](https://cmake.org/download)
* [Make](http://gnuwin32.sourceforge.net/packages/make.htm)
* [Python3](https://www.python.org/downloads) with installed [requirements](https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/requirements.txt)
