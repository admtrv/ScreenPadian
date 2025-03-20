cmake_minimum_required(VERSION 3.16)
project(ScreenPadian LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(screenpadian main.cpp)
target_compile_options(screenpadian PRIVATE -Wall -Wextra -Wpedantic -O2)

install(TARGETS screenpadian RUNTIME DESTINATION /usr/local/bin)
