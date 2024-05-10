#include <brew65emu/components/io_decoder.h>

using namespace brew65emu::components;

void IO_Decoder::update(uint8_t &io_bus, uint16_t addr_bus)
{
    if (addr_bus >> 8 == 0x7F)
    {
        io_bus = 1 << ((addr_bus >> 6 & 0b11) + 4);
        io_bus |= 1 << (addr_bus >> 4 & 0b11);
    }
}
