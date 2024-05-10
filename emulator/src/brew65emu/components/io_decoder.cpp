#include <brew65emu/components/io_decoder.h>

using namespace brew65emu::components;

void IO_Decoder::update(std::bitset<8> &io_bus, const std::bitset<16> &addr_bus)
{
    unsigned long addr = addr_bus.to_ulong();
    if (addr >> 8 == 0x7F)
    {
        io_bus = 1 << ((addr >> 6 & 0b11) + 4);
        io_bus |= 1 << (addr >> 4 & 0b11);
    }
}