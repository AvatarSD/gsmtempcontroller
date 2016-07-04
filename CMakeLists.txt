
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)


project("gsmtempcontroller")

SET(mcu "atmega2560")
SET(fcpu "16000000UL")
SET(flags "-Wall")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${mcu} -DF_CPU=${fcpu} ${flags}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmcu=${mcu} -DF_CPU=${fcpu} ${flags}")

file(GLOB_RECURSE EXE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${EXE_SRC})


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    avr-size -A -t ${PROJECT_NAME})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    avr-objcopy -j .text -j .data -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex ${PROJECT_NAME} ${PROJECT_NAME}_eeprom.hex)
