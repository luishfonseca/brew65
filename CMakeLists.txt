cmake_minimum_required(VERSION 3.27)

project(
    brew65emu
    VERSION 0.1
    DESCRIPTION "Emulator for my 6502-based homebrew computer"
    LANGUAGES CXX C)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_subdirectory(emulator/lib)
add_subdirectory(emulator/src)
