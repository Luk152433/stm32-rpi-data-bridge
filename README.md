Mini system akwizycji danych: STM32 ↔ Raspberry Pi 3 B+
------------------------------------
Krótki projekt demonstracyjny embedded + Linux:

STM32F103 (LL, bez RTOS) odczytuje BME280 po I²C, pakuje ramki i wysyła po UART (DMA TX).

RPi# (Raspberry Pi OS, C++) odbiera strumień z /dev/serial0, składa ramki, weryfikuje CRC16 i wypisuje dane.

Kolejny etap refaktorycazja kodu.

Sprzęt
------------------------------------
MCU: STM32F103 Nucleo

Czujnik: BME280 (I²C, 3V3)

Gateway: Raspberry Pi 3 B+ (Raspberry Pi OS )

Poziomy: 3.3V (UART)

STM32 - build & flash
------------------------------------
Otwórz projekt stm32 w CubeIDE.

Zbuduj (Release/Debug).

Wgraj przez ST-Link

RPi3 - build & run
------------------------------------
cd rpi_gateway

mkdir -p build && cd build

cmake ..

make -j

./rpi_gateway

