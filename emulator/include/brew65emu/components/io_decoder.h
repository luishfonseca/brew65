#pragma once

#include <cstdint>

namespace brew65emu::components
{
    class IO_Decoder
    {
    public:
        void update(uint8_t &io_bus, uint16_t addr_bus);
    };
}
