#pragma once

#include <vector>
#include <bitset>

namespace brew65emu::components
{
    class Memory
    {
    public:
        void update(std::bitset<8> &data_bus, const std::bitset<16> &addr_bus, bool write_enable, bool output_enable);
        void update_bank(const std::bitset<16> &addr_bus, const std::bitset<8> &data_bus, const std::bitset<8> &io_bus, bool irq, bool reset);

        const std::vector<uint8_t> &get_ram();
        const std::vector<uint8_t> &get_flash();
        int get_active_bank();
        bool is_in_irq_or_reset();

    private:
        std::vector<uint8_t> ram = std::vector<uint8_t>(512 * 1024, 0x00);
        std::vector<uint8_t> flash = std::vector<uint8_t>(256 * 1024, 0x00);

        int prev_bank = 0;
        bool irq_reset = false;

        int bank = 0;
    };
}