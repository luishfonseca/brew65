#pragma once

#include <cstdint>
#include <string>
#include <functional>

namespace brew65emu::tools
{
    class Disassembler
    {
    public:
        Disassembler(std::function<uint8_t(uint16_t)> read) : read(read) {}

        std::string disassemble_opcode(uint16_t addr, uint16_t &next);

    private:
        std::function<uint8_t(uint16_t)> read;
    };
}
