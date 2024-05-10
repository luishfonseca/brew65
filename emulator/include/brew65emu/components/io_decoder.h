#pragma once

#include <bitset>

namespace brew65emu::components
{
    class IO_Decoder
    {
    public:
        void update(std::bitset<8> &io_bus, const std::bitset<16> &addr_bus);
    };
}
