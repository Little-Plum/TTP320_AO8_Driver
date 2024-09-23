set(TTP_TARGET_NAME "FIRMWARE.elf")
include_directories(${CMAKE_CURRENT_LIST_DIR}/Inc)

include(${CMAKE_CURRENT_LIST_DIR}/port/stm32/stm32.cmake)

file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/Src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/*.cpp
)

target_sources(${TTP_TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Src/TTP320_AO8.c
)

