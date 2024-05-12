add_library(mos6502)
target_sources(mos6502 PRIVATE 6502/mos6502.cpp)
target_include_directories(mos6502 PUBLIC 6502)

