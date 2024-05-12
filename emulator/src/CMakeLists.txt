add_library(brew65emu)
target_link_libraries(brew65emu PUBLIC mos6502 da65)
target_include_directories(brew65emu PUBLIC ../include)
target_sources(brew65emu PRIVATE
    brew65emu/components/io_decoder.cpp
    brew65emu/components/memory.cpp
    brew65emu/interface/panel.cpp
    brew65emu/interface/renderer.cpp
    brew65emu/tools/disassembler.cpp
)

add_executable(emulator main.cpp)

target_compile_options(emulator PUBLIC -sUSE_SDL=2)
target_link_options(emulator PUBLIC -sUSE_SDL=2 -sMINIFY_HTML=0 --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell.html)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(emulator PUBLIC -sASSERTIONS=2 -fsanitize=undefined -fsanitize=address)
    target_link_options(emulator PUBLIC -sASSERTIONS=2 -fsanitize=undefined -fsanitize=address)
endif()

target_link_libraries(emulator brew65emu)
