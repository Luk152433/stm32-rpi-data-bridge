cmake_minimum_required(VERSION 3.16)
project(rpi_gateway LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)


include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)


add_executable(rpi_gateway
    src/main.cpp
    src/serial.cpp
    src/crc16.cpp
)
