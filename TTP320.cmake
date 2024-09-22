include_directories(${CMAKE_CURRENT_LIST_DIR}/Inc)

include(${CMAKE_CURRENT_LIST_DIR}/port/pc_simulate/pc.cmake)

file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/Src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/*.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Src/TTP320_AO8.c
)

