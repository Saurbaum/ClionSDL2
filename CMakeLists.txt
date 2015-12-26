cmake_minimum_required(VERSION 3.1)
project(sdlTest)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${SDL2_LINKER}")

set(SOURCE_FILES main.cpp Player/Player.cpp Player/Player.h World/World.cpp World/World.h Interface/IStateMachine.h StateController/StateController.cpp StateController/StateController.h)
add_executable(sdlTest ${SOURCE_FILES})

target_link_libraries(sdlTest ${SDL2_LIBRARY})